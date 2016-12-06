#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <QTime>
#include <math.h>
#include <cstdio>
#include <cstdlib>

#include "ofpwrp.h"

void OFPWRP::createFromStream( std::istream& file )
{
	char magic[4];
	file.read( magic, 4 );
	if( magic[0] != '4' || magic[1] != 'W' || magic[2] != 'V' || magic[3] != 'R' )
	{
		throw OFPWRP_Exception("WRP: Not a 4WVR file!");
	}

	file.read( reinterpret_cast<char*>(&xsize), 4 );
	file.read( reinterpret_cast<char*>(&ysize), 4 );

	// now, read in the elevations...
	int cellcount = xsize * ysize;
	for( int i = 0; i < cellcount; ++i )
	{
		short s;
		file.read( reinterpret_cast<char*>(&s), 2 );
		elevations.push_back( convertElevation(s) );
	}

	// the texture indices
	for( int i = 0; i < cellcount; ++i )
	{
                short index;
                file.read( reinterpret_cast<char*>(&index), 2 );
		textureIndices.push_back(index);
	}

	// now the texture paths!
	for( int i = 0; i < 512; ++i )
	{
		char texture[32];
		file.read( &texture[0], 32 );
		textures.push_back( std::string(texture) );
	}

	while( !file.eof() )
	{
		Object obj;
		file.read( reinterpret_cast<char*>(&obj), sizeof(Object) );
		strcpy (obj.path, strlwr(obj.path));
		objects.push_back( obj );
	}

}


void OFPWRP::saveWRP( std::ostream& saved )
{
	char magic[] = "4WVR";
        saved.write( magic, 4 );

        saved.write( reinterpret_cast<char*>(&xsize), 4 );
        saved.write( reinterpret_cast<char*>(&ysize), 4 );

        // now, read in the elevations...
        int cellcount = xsize * ysize;
        for( int i = 0; i < cellcount; ++i )
        {
		short s;
                s = elevations[i] * 22.222f;
                saved.write( reinterpret_cast<char*>(&s), 2 );
        }

        // the texture indices
        for( int i = 0; i < cellcount; ++i )
        {
                short index;
		index = textureIndices[i];
                saved.write( reinterpret_cast<char*>(&index), 2 );
        }

        // now the texture paths!
        for( int i = 0; i < 512; ++i )
        {
            saved.write(textures[i].c_str(), 32);
        }

        std::vector<Object>::iterator it;
        for ( it=objects.begin() ; it < objects.end(); it++ )
        saved.write ( reinterpret_cast<char*>(&(*it)), sizeof(Object) );
}


void OFPWRP::Check_Object()
{
	//std::cout << "Starting Check_Object..." << std::endl;
	//std::cout << "Check_Object: " << objects.at(1).path << std::endl;

	for (unsigned int i=0; i < objects.size(); i++)
	{
		//std::cout << "Check_Object: " << objects.at(i).path << std::endl;
		if (Find_Match(i)) Replace_Object(i);
	}
}


bool OFPWRP::Find_Match(int i)
{
	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_bush03.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush06.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush06.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush06.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush06.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush06.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_les_nw_ctver_pruhozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree06.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree06a.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree06b.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree06c.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree06.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree06a.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree06b.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree06c.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree06.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree06a.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_low_canopy.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 20;
		strcpy (TreeType[0],"vte_objects\\vte_iplant1.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_ibush01.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_itree01.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_iplant3.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_iplant1.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_ibush01.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_itree01.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_iplant3.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_iplant1.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_ibush01.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_canopy1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 4; // was 9. they are REALLY big, 4 is enough.
		strcpy (TreeType[0],"vte_objects\\vte_tree11.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree12.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree13.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree14.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree15.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree16.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree11.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree12.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree13.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree14.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_canopy2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_tree17.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush07.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush08.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_stump_tree01.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_stump_tree03.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_stump_tree04.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree17.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush07.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush07.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush08.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_canopy3.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass02.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass02.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_canopy4.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 5; // was 9. big trees, 5 is enough.
		strcpy (TreeType[0],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree18.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree18.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_grass.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass03.p3d");
		return true;
	}

	// OK
	// this is not an 50m block, maybe 5m would be too large definition for it!
	if (strcmp (objects.at(i).path,"vte_objects\\vte_grasspatch.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 1; // was 15
		strcpy (TreeType[0],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass03.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_grasspatch2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 5;
		strcpy (TreeType[0],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass03.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass03.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrassfield.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass04.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrassfield2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass05.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrassfield3.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass05.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrassfield4.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass05.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrassfield5.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass05.p3d");
		return true;
	}

	// OK
	// this is not an 50m block, maybe 5m would be too large definition for it!
	if (strcmp (objects.at(i).path,"vte_objects\\vte_igrasspatch.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 1; // was 15
		strcpy (TreeType[0],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass05.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass05.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_iles_su_ctver_pruhozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree19.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree20.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree19.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree20.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree19.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree20.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree19.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree20.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree19.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree20.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_imangrove.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree21.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_imangrove2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree22.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_imangrove3.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree23.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_imangrove4.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree24.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_imangrove5.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree22.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree23.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree24.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree21.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree22.p3d");
		return true;
	}

	// OK however this goes from bush09 to bush22 !
	if (strcmp (objects.at(i).path,"vte_objects\\vte_irssz_brush.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush09.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush10.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush11.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush12.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush13.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush14.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush15.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush16.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush17.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush18.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_irssz_brushd.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush_dry_01.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush_dry_02.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush_dry_03.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush_dry_01.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush_dry_02.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush_dry_03.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush_dry_01.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush_dry_02.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush_dry_03.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush_dry_01.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_irssz_trees.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush23.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush24.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush25.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush23.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush24.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush25.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass04.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush23.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush24.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_low_canopy2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush31.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush32.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush33.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush34.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush35.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush31.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush32.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush33.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush34.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush35.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_low_canopy3.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush36.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush37.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush36.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush37.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush36.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush37.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush36.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush37.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush36.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush37.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_low_canopy4.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_bush38.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_bush38.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_rubber.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 6; // was 9
		strcpy (TreeType[0],"vte_objects\\vte_tree_rubber01.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_tree_rubber02.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_tree_rubber03.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_tree_rubber04.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_tree_rubber01.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_tree_rubber02.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_tree_rubber03.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_tree_rubber04.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_tree_rubber01.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_tree_rubber02.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"vte_objects\\vte_tallgrass.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[1],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[2],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[3],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[4],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[5],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[6],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[7],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[8],"vte_objects\\vte_grass_tall_01.p3d");
		strcpy (TreeType[9],"vte_objects\\vte_grass_tall_01.p3d");
		return true;
	}


// OFP Resistance dated stuff

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les ctverec pruchozi_t1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les ctverec pruchozi_t2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les trojuhelnik pruchozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les_su_ctver_pruhozi_t1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les_su_ctver_pruhozi_t2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les_su_trojuhelnik.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_ctver_pruhozi_t1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_ctver_pruhozi_t2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_jehl_t1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_jehl_t2.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_jehl_trojuhelnik.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_trojuhelnik.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les ctverec.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les_su_ctver.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"data3d\\les_su_ctver_pruhozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_jehl_ctver_pruhozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// OK
	if (strcmp (objects.at(i).path,"o\\tree\\les_nw_ctver_pruhozi.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
		NumOfRandomObjects = 15;
		strcpy (TreeType[0],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[1],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[2],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[3],"ca\\plants\\dd_bush01.p3d");
		strcpy (TreeType[4],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[5],"ca\\plants\\smrk_velky.p3d");
		strcpy (TreeType[6],"ca\\plants\\les_singlestrom.p3d");
		strcpy (TreeType[7],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[8],"ca\\plants\\smrk_siroky.p3d");
		strcpy (TreeType[9],"ca\\plants\\smrk_siroky.p3d");
		return true;
	}

	// fake object trials 05-22-11
	if (strcmp (objects.at(i).path,"jungle_type_1.p3d") == 0)
	{
//		DoMyChanges = true;
//		ForestsNum++;
//		Clear_TreeType_Array();
/*
semi ok setup, but not thick enough jungle and only few tree06's and they were all the same model.
		NumOfRandomObjects = 30;
		strcpy (TreeType[0],"pmc\\vte_objects\\vte_ibush01.p3d");
		strcpy (TreeType[1],"pmc\\vte_objects\\vte_iplant1.p3d");
		strcpy (TreeType[2],"pmc\\vte_objects\\vte_iplant3.p3d");
		strcpy (TreeType[3],"pmc\\vte_objects\\vte_iplant6.p3d");
		strcpy (TreeType[4],"pmc\\vte_objects\\vte_iplant7.p3d");
		strcpy (TreeType[5],"pmc\\vte_objects\\vte_itree01.p3d");
		strcpy (TreeType[6],"pmc\\vte_objects\\vte_itree02.p3d");
		strcpy (TreeType[7],"pmc\\vte_objects\\vte_itree03.p3d");
		strcpy (TreeType[8],"pmc\\vte_objects\\vte_itree04.p3d");
		strcpy (TreeType[9],"pmc\\vte_objects\\vte_tree06.p3d");
*/
		NumOfRandomObjects = 40; // 60 works but clearly stutters on 5km viewdistance
		strcpy (TreeType[0],"pmc\\vte_objects\\vte_ibush01.p3d");
		strcpy (TreeType[1],"pmc\\vte_objects\\vte_iplant1.p3d");
		strcpy (TreeType[2],"pmc\\vte_objects\\vte_iplant3.p3d");
		strcpy (TreeType[3],"pmc\\vte_objects\\vte_iplant6.p3d");
		strcpy (TreeType[4],"pmc\\vte_objects\\vte_iplant7.p3d");
		strcpy (TreeType[5],"pmc\\vte_objects\\vte_itree01.p3d");
		strcpy (TreeType[6],"pmc\\vte_objects\\vte_itree02.p3d");
		strcpy (TreeType[7],"pmc\\vte_objects\\vte_tree06.p3d");
		strcpy (TreeType[8],"pmc\\vte_objects\\vte_tree06a.p3d");
		strcpy (TreeType[9],"pmc\\vte_objects\\vte_tree06b.p3d");
		return true;
	}

	// debug
//	Display_TreeType_Array();

//	return DoMyChanges;
/*
if we have a match

 vte_objects\vte_canopy1 	A Shau tall canopy, leafs on top
 vte_objects\vte_canopy2 	Mixed thin, low
 vte_objects\vte_canopy3 	Thin / low grass patches
 vte_objects\vte_canopy4 	Tall pinetrees
 vte_objects\vte_grass 	Low grass
 vte_objects\vte_grasspatch 	Low grass, small patch?
 vte_objects\vte_grasspatch2 	Low grass, wide patch?
 vte_objects\vte_igrassfield 	Main elephant grass(?)
 vte_objects\vte_igrassfield2 	Rice paddy rices?
 vte_objects\vte_igrassfield3 	Rice paddy rices, corner
 vte_objects\vte_igrassfield4 	Rice paddy rices, corner
 vte_objects\vte_igrassfield5 	Rice paddy rices, corner
 vte_objects\vte_igrasspatch 	Rice paddy rices, small patch?
 vte_objects\vte_iles_su_ctver_pruhozi 	PoleiKleng tall trees
 vte_objects\vte_imangrove 	Palms spread out
 vte_objects\vte_imangrove2 	One type trees spread out
 vte_objects\vte_imangrove3 	One type trees spread out
 vte_objects\vte_imangrove4 	One type trees spread out
 vte_objects\vte_imangrove5 	Trees mixed
 vte_objects\vte_irssz_brush 	Bushes
 vte_objects\vte_irssz_brushd 	Bushes, very very thin
 vte_objects\vte_irssz_trees 	Undergrowth, thick
 vte_objects\vte_les_nw_ctver_pruhozi 	Ia Drang (OFP Resistance retexture)
 vte_objects\vte_low_canopy 	Undergrowth, thick
 vte_objects\vte_low_canopy2 	Undergrowth, thick
 vte_objects\vte_low_canopy3 	Undergrowth, thick, same type
 vte_objects\vte_low_canopy4 	Ugly undergrowth, partial model?
 vte_objects\vte_rubber		Rubber trees
*/
	return false;
}


void OFPWRP::Replace_Object(int i)
{
	// replace the original object with first random guy
	strcpy (objects.at(i).path, TreeType[Get_Random_TreeType()]);

	// copy the original source values to safety
	float tmp_x = 0;
	tmp_x = objects.at(i).x;
	float tmp_z = 0;
	tmp_z = objects.at(i).z;
	// not used hmm?
	unsigned int tmp_index = 0;
	tmp_index = objects.at(i).index;

	// then begin to place X mount of random objects...
	for (int i = 0; i < NumOfRandomObjects; i++)
	{
		// create brand new empty object "tempate" where we will in new data
		Object obj;
		// replace it with new guy :)
		strcpy (obj.path, TreeType[Get_Random_TreeType()]);

		obj.x = tmp_x + Get_Random_XZ_Coord();
		obj.z = tmp_z + Get_Random_XZ_Coord();
		// what about y ?
		// obj.y = ???
		// what about index ?
		// obj.index = ???

		// rotate the newly created object randomly.
		double pi = 3.1415926535;
		float Scale = GetScale();
		float YRotation = (qrand() % 360);

		obj.rotation[0] = (float)cos(YRotation/180*pi)*Scale;
		obj.rotation[1] = 0;
		obj.rotation[2] = (float)-sin(YRotation/180*pi)*Scale;
		obj.rotation[3] = 0;
		obj.rotation[4] = Scale;
		obj.rotation[5] = 0;
		obj.rotation[6] = (float)sin(YRotation/180*pi)*Scale;
		obj.rotation[7] = 0;
		obj.rotation[8] = (float)cos(YRotation/180*pi)*Scale;

		// and write our new guy
		objects.push_back( obj );
	}
}


float OFPWRP::Get_Random_XZ_Coord()
{
	// this would need to return from -25 to 25.
	float MyRandomNum = 0;
	MyRandomNum = (-50/2 + (qrand() % 50));
//	if (lowest > MyRandomNum) { lowest = MyRandomNum; };
//	if (highest < MyRandomNum) { highest = MyRandomNum; };
//	printf("%i: obj.x: %f. MyRandomNum: %i. lowest/highest: %i/%i\n",i,obj.x,MyRandomNum,lowest,highest);
	return MyRandomNum;
}


int OFPWRP::Get_Random_TreeType()
{
	int IndexNum = 0;
	IndexNum = (qrand() % 10);
	return IndexNum;
}


float OFPWRP::GetScale()
{
	return 1;
}
