//Tcl-Tk scripts 
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <vector>
#include "Vector.h"
#include "runparam.h"
#include "particle.h" 



void tcltk_box(double Edge)
{

	string scriptfile = "/mnt/m/Runs/script.tcl";

	std::ostringstream drawbox;

	drawbox<<"draw triangle {0 0 0} {0 0 "<<Edge<<"} { "<<Edge<<" 0 "<<Edge<<"};"<<endl<<
	"draw triangle {0 0 0} { "<<Edge<<" 0 "<<Edge<<"} {"<<Edge<<" 0 0};"<<endl<<
	"draw triangle {"<<Edge<<" 0 0} {"<<Edge<<" 0 "<<Edge<<"} {"<<Edge<<" "<<Edge<<" "<<Edge<<"};"<<endl<<
	"draw triangle {"<<Edge<<" 0 0} {"<<Edge<<" "<<Edge<<" 0} {"<<Edge<<" "<<Edge<<" "<<Edge<<"};"<<endl<<
	"draw triangle {0 "<<Edge<<" 0} {0 "<<Edge<<" "<<Edge<<"} {"<<Edge<<" "<<Edge<<" "<<Edge<<"};"<<endl<<
	"draw triangle {"<<Edge<<" "<<Edge<<" "<<Edge<<"} {"<<Edge<<" "<< Edge<<" 0} {0 "<<Edge<<" 0}"<<endl<<
	"draw triangle {0 "<<Edge<<" 0} {0 "<<Edge<<" "<<Edge<<"} {0 0 0};"<<endl<<
	"draw triangle {0 "<<Edge<<" "<<Edge<<"} {0 0 "<<Edge<<"} {0 0 0};"<<endl<<
	"draw triangle {0 "<<Edge<<" "<<Edge<<"} {0 0 "<<Edge<<"} {"<<Edge<<" 0 "<<Edge<<"};"<<endl<<
	"draw triangle {0 "<<Edge<<" "<<Edge<<"} {"<<Edge<<" "<<Edge<<" "<<Edge<<"} {"<<Edge<<" 0 "<<Edge<<"};"<<endl<<
	"draw triangle {0 "<<Edge<<" 0} {"<< Edge<<" "<<Edge<<" 0} {"<<Edge<<" 0 0};"<<endl<<
	"draw triangle {0 "<<Edge<<" 0} {0 0 0} {"<<Edge<<"0 0};"<<endl;


	ofstream file(scriptfile, ios::app);
	file<<drawbox.str();
	file.close();

}


void ParticleRenderTCLTk(std::vector<Particle> &partlist)
{
	
	for(unsigned int i = 0; i<partlist.size(); i++)
	{


		if(partlist.at(i).type == 1)
		{
			V start = partlist.at(i).position + partlist.at(i).patch.unit * (Particle::L/2);
			V end = partlist.at(i).position - partlist.at(i).patch.unit * (Particle::L/2);

			int res = RunParam::render_resolution;

			void tcltk_chiral(V &start, V &end, double radius, int resolution, Patch &patch);
			tcltk_chiral(start, end, Particle::D/2, res, partlist.at(i).patch);
		}


		else if(partlist.at(i).type == 2)
		{
			int res = RunParam::render_resolution;
			V start = partlist.at(i).position + partlist.at(i).patch.unit * (Particle::L/2);
			V end = partlist.at(i).position - partlist.at(i).patch.unit * (Particle::L/2); 
			void tcltk_tip(V &start, V &end, double radius, int resolution);
			tcltk_tip(start, end, Particle::D/2,res);
		}
	}
}



void tcltk_chiral(V &start, V &end, double radius, int resolution, Patch &patch)
{
	
	string scriptfile = "/mnt/m/Runs/script.tcl";

	string patch_color = RunParam::patch_color;
	string default_color = RunParam::default_color;

	std::ostringstream sc_write;
	sc_write<<"draw color "<<default_color<<";"<<endl<<"draw cylinder "<<"{"<<start.infoRaw()<<"} "<<"{"<<end.infoRaw()<<"} "<<" radius "<<radius<<" resolution " <<resolution<<" filled yes;"<<endl<<"draw sphere "<<"{"<<start.infoRaw()<<"} "<<"radius "<<radius<<" resolution "<<resolution<<";"<<endl<<"draw sphere "<<"{"<<end.infoRaw()<<"} "<<"radius "<<radius<<" resolution "<<resolution<<";"<<endl<<"draw color "<<patch_color<<" ;"<<endl;

	V line1 = start + patch.side[0] * (Particle::D/2);
	V line2 = end + patch.side[0] * (Particle::D/2);
	sc_write<<" draw line "<<"{"<<line1.infoRaw()<<"} "<<"{"<<line2.infoRaw()<<"};"<<endl;

	V line3 = start + patch.side[1] * (Particle::D/2);
	V line4 = end + patch.side[1] * (Particle::D/2);
	sc_write<<" draw line "<<"{"<<line3.infoRaw()<<"} "<<"{"<<line4.infoRaw()<<"};"<<endl;

	V line5 = start + patch.normal * (Particle::D/2);
	V line6 = end + patch.normal * (Particle::D/2);
	sc_write<<" draw line "<<"{"<<line5.infoRaw()<<"} "<<"{"<<line6.infoRaw()<<"};"<<endl;
	

	ofstream file(scriptfile, ios::app);
	file<<sc_write.str();
	file.close();

}


void tcltk_tip(V &start, V &end, double radius, int resolution)
{
	
	string scriptfile = "/mnt/m/Runs/script.tcl";

	string patch_color = RunParam::patch_color;
	string default_color = RunParam::default_color;

	std::ostringstream sc_write;
	sc_write<<"draw color "<<default_color<<";"<<endl<<"draw cylinder "<<"{"<<start.infoRaw()<<"} "<<"{"<<end.infoRaw()<<"} "<<" radius "<<radius<<" resolution " <<resolution<<" filled yes;"<<endl<<"draw sphere "<<"{"<<start.infoRaw()<<"} "<<"radius "<<radius<<" resolution "<<resolution<<";"<<endl<<"draw color "<<patch_color<<";"<<endl<<"draw sphere "<<"{"<<end.infoRaw()<<"} "<<"radius "<<radius<<" resolution "<<resolution<<";"<<endl;

	ofstream file(scriptfile, ios::app);
	file<<sc_write.str();
	file.close();
}