# 说明      
========================================  
该代码是QT+QpenGL的示例.代码中采用了QGLWidget类进行派生.经修改,示例可以实现坐标点的显示,以及鼠标中键缩放画面,右键拖动画面.           
   
由于使用QGLWidget时,需要依赖库opengl,不方便跨平台编写代码,因此不建议采用,建议采用QOpenGLWidget类作为基类.         
  
NOTE:采用QOpenGLWidget作为基类时,界面上如何显示文字的问题尚未解决.    