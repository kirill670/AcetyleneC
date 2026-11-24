class Counter
{
public:
    TInt m_value;
    Counter();
    TInt Get();
    void Add(TInt amount);
    TInt Twice();
};

Counter::Counter()
{
    m_value = 0;
}

TInt Counter::Get()
{
    return m_value;
}

void Counter::Add(TInt amount)
{
    m_value = m_value + amount;
}

TInt Counter::Twice()
{
    Add(m_value);
    return Get();
}

GLDEF_C TInt E32Main()
{
    Counter c;
    c.Add(5);
    return c.Twice();
}
