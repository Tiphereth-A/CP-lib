from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

import pytest
from click.testing import CliRunner

from libs.cmd.bench import run_benchmarks


@pytest.mark.unit
class TestBenchCommands:
    def _write_bench(self, bench_dir: Path, args: list[str]) -> Path:
        src = bench_dir / 'bench.cpp'
        src.write_text(
            '/*comparison\n' + '\n'.join(args) + '\n*/\nint main() {}\n',
            encoding='utf-8',
        )
        return src

    def test_run_benchmarks_dry_run_collects_cmds(self, tmp_path):
        bench_dir = tmp_path / 'bench'
        bench_dir.mkdir()
        self._write_bench(bench_dir, ['--alpha', '--beta'])

        bin_dir = tmp_path / 'bin'
        raw_dir = tmp_path / 'raw'
        raw_dir.mkdir()
        (raw_dir / 'stale.json').write_text('{}', encoding='utf-8')
        compare_dir = tmp_path / 'compare'
        compare_dir.mkdir()

        with patch('libs.cmd.bench.run_command', return_value=[]) as mock_run:
            with patch('libs.cmd.bench.subprocess.run') as mock_subprocess:
                cmds = run_benchmarks(
                    str(bench_dir),
                    str(bin_dir),
                    str(raw_dir),
                    str(compare_dir),
                    2,
                    True,
                )

        assert not (raw_dir / 'stale.json').exists()
        mock_run.assert_called_once()
        mock_subprocess.assert_not_called()
        assert {cmd[-1] for cmd in cmds} == {'--alpha', '--beta'}
        assert all(cmd[:3] == ['uv', 'run', 'python'] for cmd in cmds)
        assert all(cmd[4] == 'filters' for cmd in cmds)

    def test_run_benchmarks_executes_comparisons(self, tmp_path):
        bench_dir = tmp_path / 'bench'
        bench_dir.mkdir()
        self._write_bench(bench_dir, ['--alpha'])

        bin_dir = tmp_path / 'bin'
        raw_dir = tmp_path / 'raw'
        compare_dir = tmp_path / 'compare'

        with patch('libs.cmd.bench.run_command', return_value=[]):
            with patch('libs.cmd.bench.subprocess.run', return_value=SimpleNamespace(stdout='ok')) as mock_run:
                cmds = run_benchmarks(
                    str(bench_dir),
                    str(bin_dir),
                    str(raw_dir),
                    str(compare_dir),
                    1,
                    False,
                )

        assert cmds == []
        mock_run.assert_called_once()

    def test_run_benchmarks_raises_when_no_sources(self, tmp_path):
        bench_dir = tmp_path / 'bench'
        bench_dir.mkdir()
        bin_dir = tmp_path / 'bin'
        raw_dir = tmp_path / 'raw'
        compare_dir = tmp_path / 'compare'

        with pytest.raises(RuntimeError):
            run_benchmarks(
                str(bench_dir),
                str(bin_dir),
                str(raw_dir),
                str(compare_dir),
                1,
                True,
            )

    def test_bench_cli_dry_run_prints_commands(self, cli, tmp_path):
        runner = CliRunner()
        bench_dir = tmp_path / 'bench'
        bench_dir.mkdir()
        with patch('libs.cmd.bench.run_benchmarks', return_value=[['echo', 'hi']]):
            result = runner.invoke(
                cli, ['bench', '-s', str(bench_dir), '--dry-run'])
        assert result.exit_code == 0
        assert result.output == 'echo hi\n'
