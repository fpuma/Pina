using System.IO;

[module: Sharpmake.Include(@"..\..\sharpmakeutils\utils\*")]

[module: Sharpmake.Include(@"..\pina\*")]
[module: Sharpmake.Include(@"..\extern\*")]

public static class SharpmakeMainClass
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments sharpmakeArgs)
    {
        sharpmakeArgs.Generate<Puma.PinaSolution>();
    }
}

