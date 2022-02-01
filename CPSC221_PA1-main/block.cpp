#include "block.h"
#include <cmath>
#include <iostream>
#include <algorithm>

/* Returns the width, in pixels
 * of the current block
 */
int Block::width() const
{
    return data[0].size();
}

/* Returns the heihgt, in pixels
 * of the current block
 */
int Block::height() const
{
    return data.size();
}

/* Given an image whose size is large enough, place
 * the current block in the image so that its upper left corner
 * is at position column, row. Existing pixels in the image
 * will be replaced by those of the block.
 */
void Block::render(PNG &im, int column, int row) const
{
    for (int y = row; y < row + height(); y++)
    {
        for (int x = column; x < column + width(); x++)
        {
            *im.getPixel(x, y) = data[y - row][x - column];
        }
    }
}

/* create a block of pixels whose color values are the same as the
 * rectangle in the image described by the upper left corner (column, row)
 * whose size is width x height.
 */
void Block::build(PNG &im, int column, int row, int width, int height)
{
    for (int y = row; y < row + height; y++)
    {
        vector<HSLAPixel> tempRow;
        for (int x = column; x < column + width; x++)
        {
            tempRow.push_back(*im.getPixel(x, y));
        }
        data.push_back(tempRow);
    }
}

/* Flip the current block across its horizontal midline.
 * This function changes the existing block.
 */
void Block::flipVert()
{
    reverse(begin(data), end(data));
}

/* Flip the current block across its vertical midline.
 * This function changes the existing block.
 */
void Block::flipHoriz()
{
    for (int y = 0; y < height(); y++)
    {
        reverse(begin(data[y]), end(data[y]));
    }
}

/* Rotate the current block 90 degrees clockwise.
 * This function changes the existing block.
 */
void Block::rotateRight()
{
    vector<vector<HSLAPixel>> nData;
    for (int x = 0; x < width(); x++)
    {
        vector<HSLAPixel> tempRow;
        for (int y = height() - 1; y >= 0; y--)
        {
            tempRow.push_back(data[y][x]);
        }
        nData.push_back(tempRow);
    }
    data = nData;
}
