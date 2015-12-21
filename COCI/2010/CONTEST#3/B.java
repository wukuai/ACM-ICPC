import java.lang.reflect.Array;
import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class Main {
    FastScanner in;
    PrintWriter out;

    public void solve() throws IOException {
        String num1 = in.nextString();
        String num2 = in.nextString();
        String minimum1 = "", minimum2 = "";
        String maximum1 = "", maximum2 = "";
        for(int i = 0; i < num1.length(); ++i) {
            char ch = num1.charAt(i);
            if(ch == '6') {
                minimum1 += "5";
            }
            else {
                minimum1 += ch;
            }
            if(ch == '5') {
                maximum1 += "6";
            }
            else {
                maximum1 += ch;
            }
        }
        for(int i = 0; i < num2.length(); ++i) {
            char ch = num2.charAt(i);
            if(ch == '6') {
                minimum2 += "5";
            }
            else {
                minimum2 += ch;
            }
            if(ch == '5') {
                maximum2 += "6";
            }
            else {
                maximum2 += ch;
            }
        }
        BigInteger add11 = new BigInteger(minimum1);
        BigInteger add12 = new BigInteger(minimum2);
        BigInteger add21 = new BigInteger(maximum1);
        BigInteger add22 = new BigInteger(maximum2);
        add11 = add11.add(add12);
        add21 = add21.add(add22);

        out.println(add11.toString() + " " + add21.toString());
    }

    public void run(boolean debugMode) {
        if(debugMode) {
            try {
                in = new FastScanner(new File("2024.in"));
                out = new PrintWriter(new File("2024.out"));

                solve();

                out.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else {
            try {
                in = new FastScanner(System.in);
                out = new PrintWriter(System.out);

                solve();
                out.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        public FastScanner(InputStream f) {
            br = new BufferedReader(new InputStreamReader(f));
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
        }

        String nextString() {
            return next();
        }
    }

    public static void main(String[] arg) {
        new Main().run(false);
    }
}
