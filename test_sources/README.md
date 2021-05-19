All Travis testing of the model loading library is held here.</br>
The folder is only applied when uploading code to Github repositiory.</br>

The test files in this folder are created to test out the functionality 
of the functions in Vector3D, Material, Cell and Model class.
Testing are seperated into four different files:
vector3Dtest, materialtest, celltest, and modeltest.

Stored values are initialized using set functions and check accuracy using get functions.

Errors will be counted after each function is used and result on a failed test if errors 
does not equal to zero. 
Test successful when all four test files passed.


'vector3dtest'
Test setter, getter, math operators, and functions in the Vector3D class.
Tested functions:
	void setID(int);
	void setx(double);
	void sety(double);
	void setz(double);
	
	int getID();
	void getx();
	void gety();
	void getz();

	Vector3D operation+;
	Vector3D operation-;
	Vector3D operation*;
	Vector3D cross_product;


'materialtest'
Test setter and getter functions in the Material class.
Tested functions:
	void setID(int);
	void setName(std::string);
	void setColor(Vector3D);
	void setDensity(double);

	int getID();
	std::string getName();
	Vector3D getColor();
	double getDensity();


'celltest'
Test functions in the Cell class. Calculate volume, center of gravity, and weight 
of tetrahedron, hexahedron, and pyramid.
Tested functions:
	int getID;
	int getType;
	int getMaterialID;
	std::vector<int> getIndices();
	Vector3D getCentreOfGravity();
	double getWeight();
	double getVolume();

	void setID(int);
    	void setType(int);
    	void setMaterialID(int);
    	void setIndices(std::vector<int>);
    	void pushIndice(int);
    	void insertIndice(int,int);
    	void setIndice(int,int);

	void calcWeight(std::vector<Material>);
	void calcCentreOfGravity(std::vector<Vector3D>);
	void calculateVolume(std::vector<Vector3D>); ----> for tetrahedron, hexahedron, and pyramid.


'modeltest'
Test functions in the Model class after loading model file.
Loaded model used is ExampleModel2.mod available on moodle.
Tested functions:
	bool loadModel(const char*);
	void calcModelCenter();
	void calcModelVolume();
	void calcModelWeight();
	
	Vector3D getModelCenter();
	Vector3D getModelDimensions();
	double getModelVolume();
	double getModelWeight();

	int getVectorAmount();
	int getCellAmount();
	int getMaterialAmount();

	void loadInfoToFile(char*);














