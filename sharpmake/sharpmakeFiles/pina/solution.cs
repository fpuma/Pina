using System.IO;

namespace Puma
{
    [Sharpmake.Generate]
    public class PinaSolution : Puma.Common.IMySolution
    {
        public PinaSolution()
            : base("Pina")
        {}

        public override void ConfigureAll(Configuration conf, Sharpmake.Target target)
        {
            base.ConfigureAll(conf, target);

            conf.AddProject<Puma.Pina>( target );
            conf.AddProject<Puma.PinaTests>( target );
        }
    }
}