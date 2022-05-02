namespace Puma
{
    [Sharpmake.Generate]
    class Pina : Puma.Common.IMyLib
    {
        public Pina()
            : base("Pina", @"pina")
        { }

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddPrivateDependency<Puma.Utils>(target);

            conf.IncludePrivatePaths.Add(@"\private");
            conf.IncludePaths.Add(@"\public");

            conf.PrecompHeader = @"pch.h";
            conf.PrecompSource = @"pcs.cpp";

            conf.Options.Add(Sharpmake.Options.Vc.General.TreatWarningsAsErrors.Enable);
        }
    }
}