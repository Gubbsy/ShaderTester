# Shader Tester
An OpenGL 3D program for testing and tuning Vertex and Fragment shaders.  
.obj models and Shaders are both interchangeable during runtime.

The Shader Tester is based upon the *Phong* lighting model. The position, ambient, specular and diffuse values for lighting can be adjusted dynamically to observe shader behaviour, while also providing the ability to manipulating the model's scale and rotation.

This program was created as a result of personal experiences troubleshooting and tuning custom shaders. It can be troublesome and laborious to develop shaders due to the inability to debug shader files directly and the limited feedback given from errors in runtime (due to the inability to set breakpoints and watch values). It also came about as of necessity to observe shader behaviour under variable conditions such as model position and lighting values. This Shader Tester application aims to overcome these hurdles.

There are multiple online WebGL shader editor (i.e. [Shader Frog](https://shaderfrog.com/app/editor "Shader Frog"), [The Book of Shaders](https://thebookofshaders.com/edit.php "The Boo of Shaders"), [Shader Toy](https://www.shadertoy.com "Shader Toy") ). However, the Shader Tester is unique in its ability to load custom models and dynamically manipulate light variables and pass them to the shader program n runtime. *Shader Frog* is an exception to this, as it provides a versatile Online IDE for shader development, with the ability to change the light source position. However, it still lacks the ability to change specular, ambient and diffuse values provided by OpenGL and load custom models.

The project builds upon a previous *Model Loader* code base, with improvement made to error handling, implementing the prior .obj reader and Model architecture.

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
* Upon initial boot you will be greeted with an input termial window and a OpenGL 3D window, with the default 'Creeper' model rendered using the provided default shader. *(The default shader merely uses the models Frag and Texture values with no lighting)*

* To compile and render a *Shader* using your own or one of the other provided files, press **'Q'** within the *OpenGL Window*, the *Console* will then prompt you to enter the *relative* path to the desired shader, followed by the **'ENTR'** key.   
If the path does not exist you will be prompted to re-enter a valid the path.  
If the shader does not compile the shader error log will be displayed in the console and the program will revert to using the default shader.

* To load an .obj model into the program, press **'E'** within the *OpenGL Window*, the *Console* will then prompt you to enter the relative path to your chosen model, followed by he **'ENTR'** key.
If the path does not exist or is not supported, the Console will display an warning message.
If the .obj file cannot be loaded, the Console will display an error message. You must then press **'M'** within the *OpenGL* window to load another model.

* To manipulate the model use the **'Directional Arrows'** to adjust the rotation and **'+ / -'** keys to adjust the objects scale.

* To swing the light-source position around the scene used the **'W / A / S / D'** keys.

* To adjust lighting value within the view, use: **'Z / X'** to increase or decrease the *Ambient* value, **'C / V'** to increase or decrease the *Diffuse* value and **'B / N'** to increase or decrease the *Specular* value.

* To print the current lighting values to the *Console*, press **'P'**.

## Provided material
Include with the application are a number of models and shaders for you to test for yourself.

#### Models
*Minecraft Steve* - models/minecraft-steve/minecraft-steve.obj  
*Creeper* - models/creeper/creeper.obj  
*Low Poly Boat* - models/boat/boat.obj  
*Sphere* - models/sphere/sphere.obj  
*Pyramid* - models/pyramid/pyramid.obj  

#### Shaders
*Specular* : Uses specular light and shine to give light reflection.  

 - media/specular.vert  
 - media/specular.frag


*Toon* : Uses light intensity to apply shade mask based on the amount of light on a vertex.
- media/toon.vert
- media/toon.frag


*Trippy* : Uses the normalised light intensity to apply colour multiplication using sin, cos and tan. Results in a purple or orange hue dependant on diffuse and with green lightning strike that move with the light source angle.

- media/trippy.vert
- media/trippy.frag

*Default* : Uses the vertex colour and textures without lighting.  

- media/default.vert
- media/default.frag

## Controls
M ~ Prompt model loading.  
Q ~ Prompt shader loading.  
ESC ~ Close program.

#### Light Manipulation  
A / D - Move light source  
Z / X - Increase & Decrease Ambient Light Value  
C / V - Increase & Decrease Diffuse Light Value  
P - Print current light values

#### Model Rotations  
Up Arrow ~ Rotate forward  
Left Arrow ~ Rotate left  
Down Arrow ~ Rotate backwards  
Left Arrow ~ Rotate right  

#### Model Scale
NUM PAD + ~ Scale up  
NUM PAD * ~ Scale down

## Architecture
The main Architectural principles of the software are as follows:

### Swapping and Manipulating Shaders
* The application focuses around the *Shader Manager*, this Singleton class is responsible for passing data to the desired shaders in runtime, while manging the currently active shader and it's state.   
The shader manager binds variables to their corresponding shader properties. Being a *Singleton*, the Shader Manager is only instantiated once, avoiding a 'split-brain' like scenario arising, where-by multiple Shader Mangers may attempt conflicting Manipulations upon the Shader Program. A Singleton ensures there is only a single point of access and object responsible for communicating between OpenGL and the Shader Program. This also means, that where required, a responsible class can access the shader manager and pass values to manipulate the compiled shaders.

* When any manipulation is performed on the lighting model or a new shader is being loaded an instance of the shader manager is acquired through a static accessor. The manipulation values / file paths are then passed to the shader through this instance.

* When loading a shader, the shader manager creates a new shader through the Load Shader class. This shader is then passed into OpenGL to use as it's shader program, and the previously loaded shader is deleted to deallocate memory.

* When manipulating values within the current shader program, the Shader Manger stores the current values used in the shader. When the respective functions are called, the Shader Manager updates these values and binds the new values to the current shader.


### Loading and Rendering Models
* When selecting a model to load: the file path is extracted handed to the **ObjReader**  which returns a pointer to a **Model**.  
This model assigned to the main **Model** variable within the program, who's **Draw** methods are called every game loop.
 * A Model is compose of a vector of type **Object**, which is composed of a vector of type **Mesh**.
 * When the Draw method is called on a Model, the Draw method is called for each composing **Object**, and in turn the Draw method on each **Mesh**.

 * The final Draw call on the cascaded **Mesh** binds the Vertex Array and applies any textures and passes material lighting values to the Shader Manager.

* In a similar vein to creating a model. Calling the Delete method on a model will cascade down to the composing Meshes and call its respective Delete method to deallocate memory.


### Classes

#### Main
* Stores the current model rendered.
* Handles user input.
* Contains the main display loop & logic

#### Shader manager
* Create shader using Shader Loader.
* Pass shader into Shader Program.
* Bind variables with shader properties.
* Swap shader used in the shader program.
* Manipulate variables in shader.

##### Shader Loader
* Loads shader files and creates a shader.

#### OBJ Reader
* Parse file extracting Vertex data: normals, vertices, colours, indices, materials and construct a model.
  * Construct a new Object upon reaching a new object identifier 'o'.
  * Construct a new Mesh upon reaching a use material identifier 'usemtl'.
  * All meshes are added to their respective object, with objects then being added to the model.

#### Model  
* Holds a vector of objects that compose a model
* Hold the models position, scale and rotational data and relevant methods for their manipulation.

#### Object
* Hold a vector of meshes that compose an object

#### Mesh
* Contain a vector of Vertex structs.
* Hold a material object.
* Initialise and Bind Vertex and material data to relative VBO and VAO.
* Pass data to shader. (Using the single Shader Manager instance)

#### Material  
* Stores the material data relevant to each mesh extracted from the .mtl file.

#### Vertex
* A Struct that holds vertices' respective texture, colour, position and normal co-ordinates.

#### Shader Loader Exception
* Throw when there is an issue loading shader files into a shader object.

#### Obj Loader Exception
* Thrown when there is an issue loading .obj file.

## Evaluations and Considerations
Although the solution provided is successful in reading and swapping of models and shaders. There are some clear improvements that could be made to the code base design to increase efficiency, speed and extendibility.  
They are as follows:
* The use of  singleton allows for the single responsibility of Shader Program communication, however, it does create an environment where class responsibility becomes hazy, as the class is globally accessible and mutatable. Dependency Injection could be another solution within the given context, but strict garbage collection and memory deallocation must be included ensuring only one instance of the class exists or is passed between dependent classes.
* Give more accurate control over the light position manipulation, the current system is restrictive.
* Abstract user input and controls into a class to reduce the clutter of he *Main* application entry point.
* Add compatibility for all versions of .obj files.
* Ensure that manual garbage collection and clean-ups are run when objects are finished with. For example when deleting and removing models from the scene, it is only the Buffer object that are unbound and the Mesh data itself is never deallocated from memory. Moreover some variables are not passed by reference, and thus have an impact upon memory.
* Allow more flexibility with regards to shader properties, the current system only supports the hard coded shader properties outlined in this document. It would be better to have users choose from a wider range of properties or even define properties they will be including in their shaders and the OpenGL values they will hold.
