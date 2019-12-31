# Shader Tester
An OpenGL 3D program for testing Vertex and Fragment shader.
An .obj model is loaded in with Shaders with both being interchangeable during runtime.

The position, ambient, specular and diffuse values for model lighting can be adjusted dynamically to observe shader behaviour, while also providing the ability to manipulating the model's scale and rotation.

This program was created as a result of personal experiences troubleshooting of custom shaders, due to the inability to debug shader files directly and the limited feedback given from errors. It also came about due to the necessity to observe shader behaviour under variable conditions such as model position and lighting values.

There are multiple online WebGL shader editor (i.e. [Shader Frog](https://shaderfrog.com/app/editor "Shader Frog"), [The Book of Shaders](https://thebookofshaders.com/edit.php "The Boo of Shaders"), [Shader Toy](https://www.shadertoy.com "Shader Toy") ).However, non of them provide the ability to load custom models and dynamically change light variables external to the shader program, with the exception of *Shader Frog*, where the light position can be changed.

The project builds upon a previous *Model Loader*, with improvement made to error handling.

## Packages, Dependencies and Versions
OpenGL Version 4.6.0  
GLEW Version 1.2.3.4  
Visual Studio 2019 16.3.6  

To install the required dependencies and packages within Visual Studio, right click on the solution and press 'Restore Nuget Packages'. Once complete, right click on the solution once more and press 'Rescan'.

## Shader Support
The following properties are supported within the vertex shader,  these properties must retain their given type and names in order to receive the appropriate values from OpenGL.

`layout( location = 0 ) in vec3 vPosition;` (Vertex Position)  
`layout( location = 1 ) in vec4 vColour;` (Vertex Colour)  
`layout( location = 2 ) in vec2 aTexCoord;`  (Vertex Texture Co*ordinates)  
`layout( location = 3 ) in vec3 vNormal;`    (Vertex Normals)


`uniform vec3 lightPos;` (Light Position)   
`uniform vec4 ambient;` (Ambient Light Val)  
`uniform vec3 dLight;` (Diffuse Light Val)  
`uniform vec3 sLight;` (Specular Light Val)  
`uniform float sShine;` (Shine Val)


`uniform mat4 mv_matrix;` (Model/View Matrix)  
`uniform mat4 p_matrix;` (Projection Matrix)


## Instructions For Use
* Upon initial boot you will be greeted with an input termial window and a OpenGl 3D window with the default 'Creeper' model rendered using the provided default shader.  *(The default shader merely uses the models Frag and Texture values)*

* To compile and render the model using your own or one of the other provided shaders, press **'Q'** within the *OpenGL Window*, the *Console* will then prompt you to enter the *relative* path to the desired shader, followed by the **'ENTR'** key.   
If the path does not exist you will be prompted to re*enter a valid the path.  
If the shader does not compile the shader error will be displayed and the program will revert to using the default shader.

* To load an .obj model into the program, press **'M'** within the *OpenGL Window*, the *Console* will then prompt you to enter the relative path to your chosen model, followed by he **'ENTR'** key.
If the path does not exist or is not supported, the Console will display an warning message.
If the .obj file cannot be loaded, the Console will display an error message. You must then press **'M'** within the *OpenGL* window to load another model.

* To manipulate the model use the **Directional Arrows** to adjust the rotation and **'+/-'** keys to adjust the objects scale.

* To swing the light-source position around the scene used the **'A/D'** keys.

* To adjust lighting value within the view, use: **'Z/X'** to increase or decrease the ambient value, **'C/V'** to increase or decrease the diffuse value and **'B/N'** to increase or decrease the specular value.


## Controls
M ~ Prompt model loading.  
Q ~ Prompt shader loading.  
ESC ~ Close program.

#### Model Rotations  
Up Arrow ~ Rotate forward  
Left Arrow ~ Rotate left  
Down Arrow ~ Rotate backwards  
Left Arrow ~ Rotate right  

#### Model Scale
NUM PAD + ~ Scale up  
NUM PAD * ~ Scale down

## Architecture
The main principles of the architecture of the software are as follows:

#### Shader Manager
* The application focuses around the Shader Manager, this Singleton class is responsible for passing data to the desired shaders in runtime, while manging the currently active shader and it's state.   
Instantiated upon the first pass through the main *display()* method; the shader manager binds variables to their corresponding shader properties. Being a *Singleton*, the Shader Manager is only instantiated once, avoid 'split-brain' like scenario arising by ensuring there is only a single object responsible for communicating between OpenGL and the Shader Program. This also means, that where required, a responsible class can access the shader manager and pass values to manipulate the compiled shaders.

* When any manipulation is performed on the lighting model or a new shader is being loaded: an instance of the shader manager is acquired through a static accessor. The manipulation values / file paths are then passed to the shader through this instance.


#### Loading and Rendering Models
* When selecting a model to load: the file path is extracted handed to the **ObjReader**  which returns a pointer to a **Model**.  
This model assigned to the main **Model** variable within the program, who's **Draw** methods are called every game loop.
 * A Model is compose of a vector of type **Object**, which is composed of a vector of type **Mesh**.
 * When the Draw method is called on a Model, the Draw method is called for each composing **Object**, and in turn the Draw method on each **Mesh**.

 * The final Draw call on the cascaded **Mesh** binds the Vertex Array and applies any textures.

* In a similar vein to creating a model. Calling the Delete method on a model will cascade down to the composing Meshes and call its respective Delete method to deallocate memory.


#### Readers
* Parse file extracting Vertex data: normals, vertices, colours, indices, materials and construct a model.

  **OBJ**
  * Construct a new Object upon reaching a new object identifier 'o'.
  * Construct a new Mesh upon reaching a use material identifier 'usemtl'.
  * All meshes are added to their respective object, with objects then being added to the model.

### Classes
#### Shader manager
* Create shader.
* Pass shader into Shader Program.
* Bind variables with shader properties.
* Swap shader used in the shader program.
* Manipulate variables in shader.

##### Shader Loader
* Loads shader files and creates a shader.

#### Model  
* Holds a vector of objects that compose a model
* Hold the models position, scale and rotational data and relevant methods for their manipulation.

#### Object
* Hold a vector of meshes that compose an object

#### Mesh
* Contain a vector of Vertex structs.
* Hold a material object.
* Initialise and Bind Vertex and material data to relative VBO and VAO.
* Pass data to shader.

#### Material
* A Class containing material information extracted from file.

#### Vertex
* A Struct that holds vertices' respective texture, colour, position and normal co*ordinates.

#### Shader Loader Exception
* Throw when there is an issue loading shader files into a shader object.

#### Obj Loader Exception
* Thrown when there is an issue loading .obj file.

## Evaluations and Considerations
Although the solution provided is successful in reading and swapping of models and shaders. There are some clear improvements that could be made to the code base to increase efficiency, speed and extendibility.  
They are as follows:
* Give more accurate control over the light position manipulation, the current system is restrictive.
* Abstract user input and controls into a class to reduce the clutter of he *Main* application entry point.
* Ensure that manual garbage collection and clean-ups are run when objects are finished with.
