Location storing source files of the software</br>
Availble classes:</br>
UI classes:</br>
MainWindow class - handles all signals and values sent from GUI. Allows interaction</br>
AppHelp class - handles a helper guide window that includes a quick review of software</br>
NewShapeChoice class - handles a window that allows to choose new shapes to view in the viewer</br>

Operation classes:</br>
ObjectHandler class - handles all object information. Stores final object source geometry information before is modified by applied effect. Used to retrieve or save into file the model source.</br>
Pipeline class - handles VTK pipeline operation. Covers filter stage, mapper stage and actor stage.</br>
ViewerHandler class - handles viewer settings and overall operation. Render the scene based on active pipeline and adds additional components to the scene if required by user</br>