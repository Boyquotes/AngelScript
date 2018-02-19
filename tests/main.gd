extends SceneTree
const CWD = ""
func _init():
	# test_loop()
	# test_fibR()
	# test_api()
	# test_resource_api()
	# test_native_func_call()
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

func loop(n):
	var ret = 0
	var i = 0
	while i < n:
		i += 1
		var j = 0
		while j < n:
			j += 1
			ret += j
	return ret

func test_loop():
	var start = OS.get_ticks_msec()
	loop(10000)
	printt("GDScript:", OS.get_ticks_msec() - start)

func test_api():
	var start = OS.get_ticks_msec()
	var i = 0
	while i < 100000:
		i += 1
		var s = Sprite.new()
		s.set_position(Vector2(100, 100))
		s.set_name("Hello")
		s.free()
	printt("GDScript:", OS.get_ticks_msec() - start)

func test_resource_api():
	var start = OS.get_ticks_msec()
	var i = 0
	while i < 100000:
		i += 1
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

func test_native_func_call():
	var c = Control.new()
	var start = OS.get_ticks_msec()
	var i = 0
	while i < 1000000:
		i += 1
		c.minimum_size_changed()
	printt("GDScript:", OS.get_ticks_msec() - start)
	c.free()
