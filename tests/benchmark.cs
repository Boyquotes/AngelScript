using Godot;
using System;

public class Control2 : Control
{
    int fibR(int n) {
	    if (n < 2) return n;
	    return (fibR(n-2) + fibR(n-1));
	}

	void benchmark_fibR() {
		int start = OS.GetTicksMsec();
		fibR(34);
		GD.Printt("C#:", OS.GetTicksMsec() - start);
	}

	int loop(int n) {
		int ret = 0;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				ret += j;
			}
		}
		return ret;
	}

	void benchmark_loop() {
		int start = OS.GetTicksMsec();
		loop(10000);
		GD.Printt("C#:", OS.GetTicksMsec() - start);
	}

    public override void _Ready()
    {
		benchmark_loop();
		benchmark_fibR();
		test_godot_api_call();
		test_resource_api();
		test_native_func_call();
	}

	public void test_godot_api_call()
    {

		int start = OS.GetTicksMsec();
        for (int i = 0; i < 100000; i++)
        {
            Sprite s = new Sprite();
            s.SetPosition(new Vector2(100, 100));
            s.SetName("Hello");
            s.Free();
        }

        GD.Printt("C#:", OS.GetTicksMsec() - start);
	}

	void test_native_func_call() {
		Control c = new Control();
		int start = OS.GetTicksMsec();
		for (int i=0; i<1000000; i++) {
			c.MinimumSizeChanged();
		}
		GD.Printt("C#:", OS.GetTicksMsec() - start);
		c.Free();
	}

	public void test_resource_api()
    {

		int start = OS.GetTicksMsec();
        for (int i = 0; i < 100000; i++)
        {
			Control c = new Control();
			Theme theme = new Theme();
			theme.SetName("My Beautiful Theme");
			ImageTexture tex = new ImageTexture();
			tex.SetName("xxx.png");
			theme.SetIcon("Button", "Normal", tex);
			c.SetTheme(theme);
			string name = c.GetTheme().GetIcon("Button", "Normal").GetName();
			c.Free();
        }

        GD.Printt("C#:", OS.GetTicksMsec() - start);
	}

}
