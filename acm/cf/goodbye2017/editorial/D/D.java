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
        RandomSequence solver = new RandomSequence();
        solver.solve(1, in, out);
        out.close();
    }

    static class RandomSequence {
        public int k;
        public int pa;
        public int pb;
        public int s;
        public int ia;
        public int ib;
        public int is;
        public int mod = 1000000007;
        public int[][] dp;

        public void solve(int testNumber, InputReader in, OutputWriter out) {
            k = in.nextInt();
            pa = in.nextInt();
            pb = in.nextInt();
            s = pa + pb;
            is = (int) Utils.inv(s, mod);
            ia = (int) Utils.inv(pa, mod);
            ib = (int) Utils.inv(pb, mod);
            dp = new int[k + 1][k + 1];
            for (int[] x : dp) Arrays.fill(x, -1);
            out.println(solve(1, 0));
        }

        public int solve(int a, int ab) {
            if (ab >= k) return ab;
            if (a + ab >= k) return (int) ((1L * ib * s - 1 + a + ab) % mod);
            if (dp[a][ab] != -1) return dp[a][ab];
            return dp[a][ab] = (int) ((1L * solve(a + 1, ab) * pa + 1L * solve(a, a + ab) * pb) % mod * is % mod);
        }

    }

    static class Utils {
        public static long inv(long N, long M) {
            long x = 0, lastx = 1, y = 1, lasty = 0, q, t, a = N, b = M;
            while (b != 0) {
                q = a / b;
                t = a % b;
                a = b;
                b = t;
                t = x;
                x = lastx - q * x;
                lastx = t;
                t = y;
                y = lasty - q * y;
                lasty = t;
            }
            return (lastx + M) % M;
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

        public int nextInt() {
            int c;
            for (c = this.read(); isSpaceChar(c); c = this.read()) {
                ;
            }

            byte sgn = 1;
            if (c == 45) {
                sgn = -1;
                c = this.read();
            }

            int res = 0;

            while (c >= 48 && c <= 57) {
                res *= 10;
                res += c - 48;
                c = this.read();
                if (isSpaceChar(c)) {
                    return res * sgn;
                }
            }

            throw new InputMismatchException();
        }

        public static boolean isSpaceChar(int c) {
            return c == 32 || c == 10 || c == 13 || c == 9 || c == -1;
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
}
