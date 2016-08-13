/********************************************************
 * Michael Cardenas                                     *
 * CSCI 135                                             *
 * 4/22/14                                              *
 *                                                      *
 * pgm.cpp                                              *
 * This program implements the image class, which       *
 * creates and manipulates pgm files.                   *
 ********************************************************/

#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class image {
	private:
		int img[100][100];
	
	public:
		//this function returns a copy of the image
		image copy() {
			return *this;
		}
		
		//this function sets all pixels to brightness b
		void fill(const int & b) {
			for(int i = 0; i < 100; i++)
				for(int j = 0; j < 100; j++)
					img[i][j] = b;
		}
		
		//this function "inverts" the image
		void invert() {
             for(int i = 0; i < 100; i++)
				for(int j = 0; j < 100; j++)
					img[i][j] = 255 - img[i][j];
		}
		
		//this functions draws the outline of a box w/ brightness b at starting point r and c
		//r = row, c = column, width = horizontal length, height = vertical length
		void box_outline(const int & b, const int & r, const int & c, 
						 const int & width, const int & height) {
			for(int i = r; i < r + height; i++)
				if(i == r || i == r + height - 1)
					for(int j = c; j < c + width; j++)
						img[i][j] = b;
				else {
					img[i][c] = b;
					img[i][c + width - 1] = b;
                }
		}
		
		//this function draws a filled box w/ brightness b at starting point r and c
		void box_filled(const int & b, const int & r, const int & c, 
						const int & width, const int & height) {
			for(int i = r; i < r + height; i++)
				for(int j = c; j < c + width; j++)
					img[i][j] = b;
		}
		
		//this functions blurs the image
		void blur() {
			image temp = copy();
			
			//blur top left corner
			img[0][0] = (img[0][0] + temp.img[0][1] + 
						temp.img[1][0] + temp.img[1][1]) / 4;
					
			//blur top right corner
			img[0][99] = (img[0][99] + temp.img[0][98] + 
						 temp.img[1][99] + temp.img[1][98]) / 4;
					
			//blur bottom left corner
			img[99][0] = (img[99][0] + temp.img[99][1] + 
						 temp.img[98][0] + temp.img[98][1]) / 4;
	
			//blur bottom right corner
			img[99][99] = (img[99][99] + temp.img[99][98] + 
						  temp.img[98][99] + temp.img[98][98]) / 4;
			
			for(int i = 0; i < 100; i++)
				for(int j = 0; j < 100; j++)
					//top edge
					if(i == 0 && !(j == 0 || j == 99))
						img[i][j] = (temp.img[i][j-1] + img[i][j] + temp.img[i][j+1] + 
									temp.img[i+1][j-1] + temp.img[i+1][j] + temp.img[i+1][j+1]) / 6;
					//bottom edge
					else if(i == 99 && !(j == 0 || j == 99))
						img[i][j] = (temp.img[i-1][j-1] + temp.img[i-1][j] + temp.img[i-1][j+1] + 
									temp.img[i][j-1] + img[i][j] + temp.img[i][j+1]) / 6;
					//left edge
					else if(j == 0 && !(i == 0 || i == 99))
						img[i][j] = (temp.img[i-1][j] + temp.img[i-1][j+1] + img[i][j] + 
									temp.img[i][j+1] + img[i+1][j] + temp.img[i+1][j+1]) / 6;
					//right edge
					else if(j == 99 && !(i == 0 || i == 99))
						img[i][j] = (temp.img[i-1][j-1] + temp.img[i-1][j] + temp.img[i][j-1] + 
									img[i][j] + img[i+1][j-1] + temp.img[i+1][j]) / 6;
					//everything else
					else if(!(i == 0 || i == 99) && !(j == 0 || j == 99))
						img[i][j] = (temp.img[i-1][j-1] + temp.img[i-1][j] + temp.img[i-1][j+1] + 
									temp.img[i][j-1] + img[i][j] + temp.img[i][j+1] +
									temp.img[i+1][j-1] + temp.img[i+1][j] + temp.img[i+1][j+1]) / 9;
		}
		
		//this functions reads the image from the file "image_in.pgm"
		void read() {
			int b;
			std::ifstream fin("image_in.pgm");
			
			fin.seekg(16);
			
			for(int i = 0; i < 100; i++)
				for(int j = 0; j < 100; j++) {
					fin >> b;
					img[i][j] = b;
				}
			
			fin.close();
		}
		
		//this functions writes the image from the file "image_out.pgm"
		void write() {
			std::ofstream fout("image_out.pgm");
			
			fout << "P2" << endl
				 << "100 100" << endl
				 << "255";
			
			for(int i = 0; i < 100; i++) {
				fout << endl;
			
				for(int j = 0; j < 100; j++)
					fout << img[i][j] << " ";
			}
			
			fout.close();
		}
};

void menu() {
	cout << "1. Load" << endl
		 << "2. Save" << endl
		 << "3. Copy" << endl
		 << "4. Fill" << endl
		 << "5. Invert" << endl
		 << "6. Box Outline" << endl
		 << "7. Box Fill" << endl
		 << "8. Blur" << endl
		 << "0. Exit" << endl << endl;
}

void run() {
	image img, img2;
	int b, r, c, x, width, height;
	bool isLoad = false, error = false;
	
	while(true) {
		menu();
		cout << "Enter option: ";
		cin >> x;
		
		if(x == 0) break;
		else if(x == 1) { //load
			img.read();
			isLoad = true;
			cout << "File loaded." << endl;
		}
		else if(x == 2) //save
			if(isLoad) {
				img.write();
				cout << "File saved." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 3) //copy
			if(isLoad) {
				img2 = img.copy();
				cout << "File copied." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 4) //fill
			if(isLoad) {
				do {
					if(error)
						cout << "Value not within scope (0 - 255)" << endl;
					
					cout << "Enter pixel value: ";
					cin >> b;
					
					error = true;
				} while(b < 0 || b > 255);
				
				error = false;
				
				img.fill(b);
				
				cout << "Image filled." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 5) //invert
			if(isLoad) {
				img.invert();
				cout << "Image inverted." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 6) //box outline
			if(isLoad) {
				do { //pixel value
					if(error)
						cout << "Value not within scope (0 - 255)" << endl;
					
					cout << "Enter pixel value: ";
					cin >> b;
					
					error = true;
				} while(b < 0 || b > 255);
				
				error = false;
				
				do { //row
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter starting row: ";
					cin >> r;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //column
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter starting column: ";
					cin >> c;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //width
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter width: ";
					cin >> width;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //height
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter height: ";
					cin >> height;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				img.box_outline(b, r, c, width, height);
				
				cout << "Outline added." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 7) //box fill
			if(isLoad) {
				do { //pixel value
					if(error)
						cout << "Value not within scope (0 - 255)" << endl;
					
					cout << "Enter pixel value: ";
					cin >> b;
					
					error = true;
				} while(b < 0 || b > 255);
				
				error = false;
				
				do { //row
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter starting row: ";
					cin >> r;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //column
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter starting column: ";
					cin >> c;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //width
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter width: ";
					cin >> width;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				do { //height
					if(error)
						cout << "Value not within scope (0 - 100)" << endl;
					
					cout << "Enter height: ";
					cin >> height;
					
					error = true;
				} while(b < 0 || b > 100);
				
				error = false;
				
				img.box_filled(b, r, c, width, height);
				
				cout << "Filled outline added." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else if(x == 8) //blur
			if(isLoad) {
				img.blur();
				cout << "Image blurred." << endl;
			}
			else cout << "No image has been loaded." << endl;
		else cout << "Command not recognized." << endl;
	}
}

int main() {
	run();
	
	return 0;
}
