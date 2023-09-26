namespace n
{
struct S
{
    friend struct C;

  private:
    int i = 2;
};

struct C
{
    int f()
    {
      n::S s;
      return s.i;
    }
};
}

int main()
{
}