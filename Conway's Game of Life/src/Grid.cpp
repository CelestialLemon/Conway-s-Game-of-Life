#include "Grid.h"

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