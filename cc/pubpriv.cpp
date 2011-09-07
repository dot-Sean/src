class Base {
    private: int x;
    public: int getX();
    public: Base(int xArg): x(xArg) {}
};

int main (int argc, char * * argv) {
    Base base(100);
    return (0);
}

