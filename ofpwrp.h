#ifndef VB_OFPWRP_H
#define VB_OFPWRP_H

#include <vector>
#include <exception>
#include <string>
#include <iostream>
#include <fstream>

class OFPWRP
{
	public:
	class OFPWRP_Exception : std::exception
	{
		std::string msg;
		public:
		OFPWRP_Exception( std::string msg )
		{
			this->msg = msg;
		}
		~OFPWRP_Exception() throw() {}

		std::string toString()
		{
			return msg;
		}
	};

	struct Object
	{
		float rotation[9];	// rotation matrix
		float x, y, z;		// position on island
		unsigned int index;	// object index
		char path[76];		// path to object p3d
	};

	int xsize, ysize;
	std::vector<float> elevations;
	std::vector< std::string > textures;
        std::vector<short> textureIndices;
	std::vector<Object> objects;

	void createFromStream( std::istream& file );
        void saveWRP( std::ostream& saved );
	// foresting stuff
	void Check_Object();
	bool Find_Match(int i);
	void Replace_Object(int i);
	float Get_Random_XZ_Coord();
	int Get_Random_TreeType();
	float GetScale();

	// array of single trees, 15 trees (76 file name lenght).
	char TreeType[15][76];
	int NumOfRandomObjects;

	static float convertElevation( short s )
	{
		return static_cast<float>(s) / 22.222f;
	}
};

#endif
