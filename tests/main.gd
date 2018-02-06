extends SceneTree
const CWD = ""
func _init():
	# test_api2()
	test_fibR()
	test_api()
	test_resource_api()
	print("--------------------------------")
	var as = AngelScriptRunner.new()
	as.run(str(CWD, 'main.as'))
	print("--------------------------------")
	quit()

func fibR(n):
	if n < 2:
		return n
	return (fibR(n-2) + fibR(n-1));

func test_fibR():
	var start = OS.get_ticks_msec()
	fibR(34)
	printt("GDScript:", OS.get_ticks_msec() - start)

func test_api2():
	var start = OS.get_ticks_msec()
	for i in range(100000):
		var o = Node.new()
		o.set_meta("name", "value")
		o.get_meta("name")
		o.free()
	printt("GDScript:", OS.get_ticks_msec() - start)


func test_api():
	var start = OS.get_ticks_msec()
	for i in range(100000):
		var s = Sprite.new()
		s.set_position(Vector2(100, 100))
		s.set_name("Hello")
		s.free()
	printt("GDScript:", OS.get_ticks_msec() - start)

func test_resource_api():
	var start = OS.get_ticks_msec()
	for i in range(100000):
		var c = Control.new()
		var theme = Theme.new()
		theme.set_name("My Beautiful Theme")
		var tex = ImageTexture.new()
		tex.set_name("xxx.png")
		theme.set_icon("Button", "Normal", tex)
		c.set_theme(theme)
		var name = c.get_theme().get_icon("Button", "Normal").get_name()
		c.free()
	printt("GDScript:", OS.get_ticks_msec() - start)
