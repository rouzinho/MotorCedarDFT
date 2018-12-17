#include "plugin.h"
#include "MotorPublisher.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <MotorPublisher>("Utilities")
    );
    plugin->add(summation_decl);
}
