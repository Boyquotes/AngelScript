extends SceneTree
const CWD = "F:/work/godot/modules/angelscript/tests"
func _init():
	print("--------------------------------")
	var as = AngelScriptRunner.new()
	as.run(str(CWD, '/', 'main.as'))
	print("--------------------------------")
	quit()
