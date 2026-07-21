namespace FastIO {

    static constexpr int BUFSIZE = 1 << 20; // 1 MB

    char ibuf[BUFSIZE];
    int ipos = 0, ilen = 0;

    char obuf[BUFSIZE];
    int opos = 0;

    inline char getChar() {
        if (ipos == ilen) {
            ilen = fread(ibuf, 1, BUFSIZE, stdin);
            ipos = 0;
            if (!ilen) return EOF;
        }
        return ibuf[ipos++];
    }

    inline void putChar(char c) {
        if (opos == BUFSIZE) {
            fwrite(obuf, 1, opos, stdout);
            opos = 0;
        }
        obuf[opos++] = c;
    }

    inline void flush() {
        fwrite(obuf, 1, opos, stdout);
        opos = 0;
    }

    template<typename T>
    inline bool readInt(T &x) {
        x = 0;
        T sign = 1;
        char c = getChar();

        if (c == EOF) return false;

        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (c == EOF) return false;
        }

        if (c == '-') {
            sign = -1;
            c = getChar();
        }

        while (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
            c = getChar();
        }

        x *= sign;
        return true;
    }

    inline bool readChar(char &c) {
        c = getChar();
        if (c == EOF) return false;
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t')
            c = getChar();
        return c != EOF;
    }

    inline bool readString(std::string &s) {
        s.clear();
        char c = getChar();

        if (c == EOF) return false;

        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            c = getChar();
            if (c == EOF) return false;
        }

        while (!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) {
            s += c;
            c = getChar();
        }

        return true;
    }

    template<typename T>
    inline void writeInt(T x, char end = '\n') {

        if (x == 0) {
            putChar('0');
            if (end) putChar(end);
            return;
        }

        if (x < 0) {
            putChar('-');
            x = -x;
        }

        char s[30];
        int n = 0;

        while (x) {
            s[n++] = char('0' + x % 10);
            x /= 10;
        }

        while (n--)
            putChar(s[n]);

        if (end)
            putChar(end);
    }

    struct Flusher {
        ~Flusher() { flush(); }
    } flusher;
}

/*
usage :


int n;
FastIO::readInt(n);

long long x;
FastIO::readInt(x);

string s;
FastIO::readString(s);

FastIO::writeInt(n);
FastIO::writeInt(x, ' ');
FastIO::writeInt(123456789LL, '\n');


*/



