// Nathan Suh, Dehowe Feng

#include "grid.h"
#include "PowerMain.h"
#include <iostream>
#include <cmath>
#include "QueueAr.h"


//Notes:
// blocks is the array that is being stored in.
// adjBlocks is the array of blocks that are adjacent
// losses is the array of losses of connections.
// previous holds "previous" block of a block, i.e what block will point to that block.


using namespace std;

Grid::Grid(int gridSize, const Block *blocks, int previous[])
{
	Blockdata *blocksdata = new Blockdata[gridSize];
	Queue<Blockdata> PowerLine(gridSize*10);
	
	for(int i = 0; i < gridSize ; i++)
	{
		blocksdata[i].blocks = blocks[i];
		blocksdata[i].distance = INFINITY;
		blocksdata[i].identity = i;
		blocksdata[i].connected = false;
	}
	
	for (int i = 9; i > 0 ; i--)
	{
		blocksdata[i].distance = 0;
		PowerLine.enqueue(blocksdata[i]);
	}

	while(!PowerLine.isEmpty())
	{
		Blockdata b = PowerLine.dequeue();
		//cout << "edgeCount of b is " << b.blocks.edgeCount << endl;
		//cout << "distance of b is " << b.distance << endl;
		//cout << "identity of b is" << b.identity << endl;
		//cout << "losses of b are " << endl << b.blocks.losses[0] << endl;
		//cout << b.blocks.losses[1] << endl;
		//cout << b.blocks.losses[2] << endl;
		//cout << "adjacents are" << endl << b.blocks.adjBlocks[0] << endl;
		//cout << b.blocks.adjBlocks[1] << endl;
		//cout << b.blocks.adjBlocks[2] << endl;
 
			for(int i = 0; i < b.blocks.edgeCount; i++)
			{
				if(b.distance + b.blocks.losses[i] < blocksdata[b.blocks.adjBlocks[i]].distance)
			   {
				   if(blocksdata[b.blocks.adjBlocks[i]].identity > 9)
				   {
				   blocksdata[b.blocks.adjBlocks[i]].distance = b.distance + b.blocks.losses[i];
				   previous[b.blocks.adjBlocks[i]] = b.identity;
				   }
				   else
					   blocksdata[b.blocks.adjBlocks[i]].distance = 0;
				   
						PowerLine.enqueue(blocksdata[b.blocks.adjBlocks[i]]);
						blocksdata[b.blocks.adjBlocks[i]].connected = true;
			   }

			}
	}
	
} 


