# Bikini Studio - Resource Editor #
Bikini Studio application consists of two modules: Bikini.dll - C++ dynamic link library implementing all editor’s functionality and Studio.exe - C# application implementing editor’s user interface. Bikini.dll exposes a set of interface functions to be used by Studio.exe, and Studio.exe uses these functions via P/Invoke.

## Metaphor ##
The root entity in the editor’s object model is Workspace. Workspace is created on start-up and exists all the time the editor is running. Workspace allows user to create, save and load Project. Project contains one or several Stages. Stages may have sub-Stages defining the stages hierarchy. Each Stage has a set of Resources associated. All Stage’s resources are loaded when the Stage gets active. Stage can use its own resources and resources of all its super-Stages. Each Stage is associated with Package where all its Resources are stored when game project is being built. Project can consist of one or several Packages.

### Stages ###
Stage is an analog of state in FSM. Stage defines current Menu, Scene and Script. One of the root Stages should be set as a start-up Stage of the Project, it gets active on the application start-up.

#### Script ####
Stage’s Script handles events from Menu and Scene. Script controls behaviour of Stage’s Menu and Scene. In addition to event handling script can have a special co-routine controlling the Stage execution. When co-routine finishes execution the Stage exits, and its super-Stage gets active. Stage’s Script can activate a sub-Stage. In this case Script execution is suspended and resumes only when sub-Stage is exited. When Stage exits it can specify one of sibling-Stages as a next Stage.

#### Scene ####
Scene represents 3D world populated with Actors. Scene and Actors can generate Events handled by Stage’s Script. Script can control an Actor using a set of functions exposed by it. The functions in this set depend on set of Policies certain Actor have. Scene is a special kind of Actor and can be controlled by Script in a similar way.

#### Menu ####
Menu is used to allow user control the application and to output information on the screen. Menu generates Events for Stage’s Script. Script can control Menu using a set of functions exposed by it.
<br><i>todo</i>

<h3>Resources</h3>
All entities in a Stage (like Scene, Actors, Menu, Script and so on) are Resources.<br>
<br><i>todo</i>

<h3>Packages</h3>
Packages are files on a disc. They are created when a Project is being built.<br>
<br><i>todo</i>

<h2>User Interface</h2>
The goal of user interface is providing the user with a complete and convenient set of tools for creating and editing bikini application resources.<br>
<br>
<h3>Views</h3>
The main element of editor’s user interface is View. There is a number of View types. Each of these views serves for viewing/editing particular object or even particular object’s aspect.<br>
<br>
<h4>Project View</h4>
Serves for editing the Project stages hierarchy. Project View consist of a TreeView control displaying the Project’s stages hierarchy and a ToolBar control with all available commands. Right-click on the TreeView opens a context menu with commands available for currently selected node. Stages can be created, removed and moved. One of the root Stages can be set as a start-up Stage for the Project. Properties of a Stage currently selected in Project View are shown in Properties View and can be edited there. Double-click on a Stage in Project View opens Stage View where the Stage can be ran.<br>
<br>
<h4>Packages View</h4>
Serves for editing the stages distribution over the packages.<br>
<br><i>todo</i>