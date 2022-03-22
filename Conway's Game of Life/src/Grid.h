#pragma once

class Grid{

    private:
    unsigned int m_height;
    unsigned int m_width;

    bool** m_localBuffer;

    public:
    Grid(unsigned int widht, unsigned int height);
    ~Grid();

    void Clear();
    void SetCell(unsigned int x, unsigned int y, bool value);
    void Print() const;
};