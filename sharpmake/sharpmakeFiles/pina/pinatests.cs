namespace Puma
{
    [Sharpmake.Generate]
    class PinaTests : Puma.SharpmakeBase.IApplication
    {
        public PinaTests()
            : base("PinaTests", @"pinatests")
        {
        }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Puma.Utils>(target);
            conf.AddPrivateDependency<Puma.GoogleTest>(target);
            conf.AddPrivateDependency<Puma.Pina>(target);

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);

            conf.SolutionFolder = "Tests";
        }
    }
}