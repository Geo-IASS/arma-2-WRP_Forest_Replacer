#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include "ofpwrp.h"
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	if ( argc < 2 )
	{
		std::cout << "Not enough arguments!" << std::endl;
	}
	else
	{
		std::ifstream file( argv[1], std::ios_base::in | std::ios_base::binary );
		OFPWRP wrp;
		try
		{
			wrp.createFromStream(file);
		}
		catch( OFPWRP::OFPWRP_Exception e )
		{
                        std::cout << e.toString() << std::endl;
		}
		file.close();

		std::cout << "Object count: " << wrp.objects.size() << std::endl;
                std::cout << "Elevations: " << wrp.elevations.size() << std::endl;
                std::cout << "TextureIndices: " << wrp.textureIndices.size() << std::endl;
                std::cout << "Textures: " << wrp.textures.size() << std::endl;
                std::cout << "X size: " << wrp.xsize << " Y size: " << wrp.ysize << std::endl;

		// do the forest magic here...

		wrp.Check_Object();
		std::cout << "After single objects added: " << wrp.objects.size() << std::endl;

                // write it out to a new file
		std::ofstream saved( argv[2], std::ios_base::out | std::ios_base::binary );
                try
                {
                        wrp.saveWRP(saved);
                }
                catch( OFPWRP::OFPWRP_Exception e )
                {
                        std::cout << e.toString() << std::endl;
                }
                saved.close();

/*
                for (int i=0; i < 512; i++) {
                    std::cout << "TextureIndices[" << i << "]: " << wrp.textureIndices[i] << std::endl;
                    std::cout << "Textures[" << i << "]: " << wrp.textures[i] << std::endl;
                }
*/
        }

	std::cout << "All done, thanks." << std::endl;

        //return a.exec();
    return 0;
}
