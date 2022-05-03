namespace Puma
{
    [Sharpmake.Export]
    class GoogleTest : Puma.Common.IExternBinaries
    {
        private static readonly string RelativeSourcePath = @"googletest-release-1.10.0";
        public static readonly string FullExternSourcePath = Puma.SharpmakeUtils.GetExternPath() + @"\" + RelativeSourcePath;

        public GoogleTest()
            : base("GTest", RelativeSourcePath)
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target)
        {
            conf.IncludePaths.Add(@"\include");
        }
        
        public override void ConfigureLink(Configuration conf, Sharpmake.Target target)
        {
            conf.LibraryPaths.Add(SourceRootPath + @"\lib");

            if (target.Optimization == Sharpmake.Optimization.Debug)
            {
                conf.LibraryFiles.Add(@"gmock_maind.lib");
                conf.LibraryFiles.Add(@"gmockd.lib");
                conf.LibraryFiles.Add(@"gtest_maind.lib");
                conf.LibraryFiles.Add(@"gtestd.lib");

            }
            else
            {
                conf.LibraryFiles.Add(@"gmock_main.lib");
                conf.LibraryFiles.Add(@"gmock.lib");
                conf.LibraryFiles.Add(@"gtest_main.lib");
                conf.LibraryFiles.Add(@"gtest.lib");
            }

        }
    }
}