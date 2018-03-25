import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.util.ArrayList;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.math.BigInteger;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class TLE {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        GraphConnectivity solver = new GraphConnectivity();
        solver.solve(1, in, out);
        out.close();
    }

    static class GraphConnectivity {
        public void solve(int testNumber, InputReader in, OutputWriter out) {
            int n = in.nextInt();
            char[][] grid = new char[n][n];
            for (int i = 0; i < n; i++) {
                grid[i] = in.next().toCharArray();
            }

            boolean[] vis = new boolean[n];
            ArrayList<ArrayList<Integer>> comps = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (vis[i]) continue;
                ArrayList<Integer> gg = new ArrayList<>();
                vis[i] = true;
                gg.add(i);
                for (int k = 0; k < gg.size(); k++) {
                    int src = gg.get(k);
                    for (int j = 0; j < n; j++) {
                        if (vis[j]) continue;
                        if (grid[src][j] == 'A') {
                            gg.add(j);
                            vis[j] = true;
                        }
                    }
                }

                for (int j : gg)
                    for (int k : gg) {
                        if (grid[j][k] == 'X') {
                            out.println(-1);
                            return;
                        }
                    }

                if (gg.size() > 1) {
                    comps.add(gg);
                }
            }

            int m = comps.size();
            int[] base = new int[1 << m];
            int[] adj = new int[m];
            for (int i = 0; i < m; i++) {
                adj[i] |= 1 << i;
                for (int j = 0; j < m; j++) {
                    boolean bad = false;
                    for (int p : comps.get(i))
                        for (int q : comps.get(j)) {
                            if (grid[p][q] == 'X') {
                                bad = true;
                            }
                        }
                    if (!bad) {
                        adj[i] |= 1 << j;
                    }
                }
            }
            outer:
            for (int i = 0; i < 1 << m; i++) {
                for (int k = 0; k < m; k++) {
                    if (((i >> k) & 1) == 1 && (adj[k] & i) != i) {
                        continue outer;
                    }
                }
                base[i]++;
            }

            for (int level = 0; level < m; level++) {
                for (int i = 0; i < 1 << m; i++) {
                    if (((i >> level) & 1) == 1) {
                        base[i] += base[i ^ (1 << level)];
                    }
                }
            }

            int mod = (int) (Math.random() * 1000000000) + 1000000000;
            while (!BigInteger.valueOf(mod).isProbablePrime(20)) mod++;

            long[] s = new long[1 << m];
            for (int i = 0; i < 1 << m; i++) {
                s[i] = (Integer.bitCount(i) & 1) == (m & 1) ? 1 : (mod - 1);
            }
            int ans = 0;
            while (true) {
                if (AUtils.sum(s) % mod != 0) break;
                ans++;
                for (int i = 0; i < 1 << m; i++) {
                    s[i] = s[i] * base[i] % mod;
                }
            }

            out.println(n + ans - 1);
        }

    }

    static class AUtils {
        public static long sum(long[] arr) {
            long sum = 0;
            for (long x : arr) {
                sum += x;
            }
            return sum;
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
