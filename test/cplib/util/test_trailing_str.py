import pytest
from libs.util.trailing_str import trailing_str


@pytest.mark.unit
class TestTrailingStr:
    def test_short_string_unchanged(self):
        s = "hello world"
        assert trailing_str(s) == s

    def test_exactly_at_boundary(self):
        # len == start+end+5 should NOT be truncated
        s = "a" * 205  # 100+100+5 = 205
        assert trailing_str(s) == s

    def test_one_over_boundary_truncated(self):
        s = "a" * 206
        result = trailing_str(s)
        assert result == "a" * 100 + " ... " + "a" * 100

    def test_long_string_truncated(self):
        s = "x" * 300
        result = trailing_str(s, start=100, end=100)
        assert result == "x" * 100 + " ... " + "x" * 100

    def test_custom_start_end(self):
        # 20 > 5+5+5=15, so truncated
        s = "a" * 20
        result = trailing_str(s, start=5, end=5)
        assert result == "a" * 5 + " ... " + "a" * 5

    def test_custom_start_end_short(self):
        s = "ab"
        assert trailing_str(s, start=1, end=1) == "ab"

    def test_empty_string(self):
        assert trailing_str("") == ""

    def test_preserves_head_and_tail(self):
        head = "START"
        tail = "END"
        mid = "X" * 300
        s = head + mid + tail
        result = trailing_str(s, start=10, end=10)
        assert result.startswith(head)
        assert result.endswith(tail[-10:])
