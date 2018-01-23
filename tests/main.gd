extends SceneTree
const CWD = "/home/geequlim/Documents/Workspace/Develop/Godot/godot/modules/angelscript/tests"
func _init():
	print("--------------------------------")
	var as = AngelScriptRunner.new()
	as.run(str(CWD, '/', 'main.as'))
	print("--------------------------------")
	quit()
