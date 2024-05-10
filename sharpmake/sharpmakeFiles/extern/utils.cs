namespace Puma
{
    [Sharpmake.Generate]
    class Utils : Puma.SharpmakeBase.IHeaderOnly
    {
        public Utils()
            : base("Utils", @"submodules\utils")
        { }

        public override void ConfigureIncludes(Configuration conf, Sharpmake.Target target) 
        {
            conf.IncludePaths.Add(@"\include");

            conf.SolutionFolder = "Submodules";
        }
    }
}