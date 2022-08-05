namespace Puma
{
    [Sharpmake.Generate]
    class PinaTests : Puma.Common.IMyApplication
    {
        public PinaTests()
            : base("PinaTests", @"pinatests")
        {
            AdditionalSourceRootPaths.Add(GoogleTest.FullExternSourcePath);
            AdditionalSourceRootPaths.Add(Utils.FullExternSourcePath);
        }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Puma.Utils>(target);
            conf.AddPrivateDependency<Puma.GoogleTest>(target);
            conf.AddPrivateDependency<Puma.Pina>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}