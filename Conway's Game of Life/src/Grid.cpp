#include "Grid.h"
#include "Render.h"
#include <iostream>

Grid::Grid(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_localBuffer(nullptr)
{
    m_localBuffer = new bool*[m_height];

    for(unsigned int i = 0; i < m_height; i++)
    {
        m_localBuffer[i] = new bool[m_width];
    }
}

Grid::~Grid()
{
    for(unsigned int i = 0; i < m_height; i++)
        delete[] m_localBuffer[i];

    delete[] m_localBuffer;
}

void Grid::Clear()
{
    for(unsigned int y = 0; y < m_height; y++)
    {
        for(unsigned int x = 0; x < m_width; x++)
        {
            m_localBuffer[x][y] = false;
        }
    }
}

void Grid::SetCell(unsigned int x, unsigned int y, bool value)
{
    if(x >= m_width || y >= m_height) 
    {    
        throw std::out_of_range("Buffer out of bounds");
        return;
    }
    m_localBuffer[x][y] = value;
}

int Grid::numOfActiveNeighbours(int x, int y) const
{
    int ans = 0;

    for(int i = 1; i < 9; i++)
    {
        int xi = x, yi = y;
        switch(i)
        {
            case 1: xi += 0; yi += 1; break;
            case 2: xi += 1; yi += 1; break;
            case 3: xi += 1; yi += 0; break;
            case 4: xi += 1; yi += -1; break;
            case 5: xi += 0; yi += -1; break;
            case 6: xi += -1; yi += -1; break;
            case 7: xi += -1; yi += 0; break;
            case 8: xi += -1; yi += 1; break;
        }

        if(xi >= 0 && xi < m_width && yi >= 0 && yi < m_height)
        {
            if(m_localBuffer[xi][yi] == true) ans++;
        }
    }

    return ans;
}

void Grid::ConwayMutate(Grid& otherGrid)
{
    this->Clear();

    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
            int activeNeighbours = otherGrid.numOfActiveNeighbours(x, y);

            if(activeNeighbours < 2) this->SetCell(x, y, false);
            else if(activeNeighbours > 3) this->SetCell(x, y, false);
            else if(activeNeighbours == 3) this->SetCell(x, y, true);
            else if(activeNeighbours == 2 && otherGrid.GetCell(x, y) == true) this->SetCell(x, y, true); 
        }
    }
}


void Grid::Print() const
{
    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
            std::cout << m_localBuffer[x][y] << " ";
        }

        std::cout << "\n";
    }
}

void Grid::Render() const
{
    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
            if(m_localBuffer[x][y] == false) continue;

            float posX = (float)x / m_width;
            float posY = (float)(y + 1) / m_height;

            // convert from range [0, 1] to [-1, 1]
            posX = (posX * 2) - 1.0f;
            posY = (posY * 2) - 1.0f;
            posY *= -1.0f;

            float sizeX = 2.0f / m_width;
            float sizeY = 2.0f / m_height;
            
            DrawRectangle(posX, posY, sizeX, sizeY);
        }
    }
}