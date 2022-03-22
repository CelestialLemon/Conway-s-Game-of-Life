#pragma once

class Grid{

    private:
    unsigned int m_height;
    unsigned int m_width;

    bool** m_localBuffer;


    public:
    Grid(unsigned int width, unsigned int height);
    ~Grid();

    void Clear();
    void SetCell(unsigned int x, unsigned int y, bool value);
    void ConwayMutate(Grid& otherGrid);

    bool  GetCell(unsigned int x, unsigned int y) const { return m_localBuffer[x][y]; }; 
    void Print() const;
    void Render() const;
    int numOfActiveNeighbours(int x, int y) const;
};