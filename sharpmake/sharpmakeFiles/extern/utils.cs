namespace Puma
{
    [Sharpmake.Export]
    class Utils : Puma.Common.IExternBinaries
    {
        private static readonly string RelativeSourcePath = @"utilslibrary\source\utils";
        public static readonly string FullExternSourcePath = Puma.SharpmakeUtils.GetExternPath() + @"\" + RelativeSourcePath;

        public Utils()
            : base("Utils", RelativeSourcePath)
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target) 
        {
            conf.IncludePaths.Add(@"\public");
        }

        public override void ConfigureLink(Configuration conf, Sharpmake.Target target) { }
    }
}