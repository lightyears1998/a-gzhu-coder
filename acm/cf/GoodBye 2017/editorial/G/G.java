import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.io.BufferedWriter;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        SorterSum solver = new SorterSum();
        solver.solve(1, in, out);
        out.close();
    }

    static class SorterSum {
        public int mod = 1000000007;
        public int[] x;
        public int n;
        public int[][][] dp;
        public int[] s;
        public int[] p10;

        public void solve(int testNumber, InputReader in, OutputWriter out) {
            char[] e = in.next().toCharArray();
            n = e.length;
            x = new int[n];
            for (int i = 0; i < n; i++) x[i] = e[i] - '0';
            p10 = new int[n + 1];
            p10[0] = 1;
            for (int i = 1; i <= n; i++) p10[i] = (int) (1L * p10[i - 1] * 10 % mod);
            s = new int[n + 1];
            s[n] = 1;
            for (int i = n - 1; i >= 0; i--) {
                s[i] = (int) (((1L * p10[n - i - 1] * x[i]) + s[i + 1]) % mod);
            }
            dp = new int[n + 1][n + 1][2];
            int ans = 0;
            for (int dd = 1; dd <= 9; dd++) {
                for (int[][] y : dp) for (int[] z : y) Arrays.fill(z, -1);
                for (int pp = 0; pp < n; pp++) {
                    ans = (int) ((ans + 1L * p10[pp] * count(0, pp + 1, false, dd)) % mod);
                }
            }
            out.println(ans);
        }

        public int count(int pos, int need, boolean less, int dig) {
            if (need == 0) return less ? p10[n - pos] : s[pos];
            if (pos == n) return 0;
            if (dp[pos][need][less ? 1 : 0] != -1) return dp[pos][need][less ? 1 : 0];

            int lim = less ? 10 : (x[pos] + 1);
            int res = 0;
            for (int i = 0; i < lim; i++) {
                res += count(pos + 1, need - (i >= dig ? 1 : 0), less || (i < x[pos]), dig);
                if (res >= mod) res -= mod;
            }
            return dp[pos][need][less ? 1 : 0] = res;
        }

    }

    static class OutputWriter {
        private final PrintWriter writer;

        public OutputWriter(OutputStream outputStream) {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }

        public OutputWriter(Writer writer) {
            this.writer = new PrintWriter(writer);
        }

        public void close() {
            writer.close();
        }

        public void println(int i) {
            writer.println(i);
        }

    }

    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1 << 16];
        private int curChar;
        private int numChars;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (this.numChars == -1) {
                throw new InputMismatchException();
            } else {
                if (this.curChar >= this.numChars) {
                    this.curChar = 0;

                    try {
                        this.numChars = this.stream.read(this.buf);
                    } catch (IOException var2) {
                        throw new InputMismatchException();
                    }

                    if (this.numChars <= 0) {
                        return -1;
                    }
                }

                return this.buf[this.curChar++];
            }
        }

        public String next() {
            int c;
            while (isSpaceChar(c = this.read())) {
                ;
            }

            StringBuilder result = new StringBuilder();
            result.appendCodePoint(c);

            while (!isSpaceChar(c = this.read())) {
                result.appendCodePoint(c);
            }

            return result.toString();
        }

        public static boolean isSpaceChar(int c) {
            return c == 32 || c == 10 || c == 13 || c == 9 || c == -1;
        }

    }
}
