#include "plugin.h"
#include "EarSubscriber.h"
#include <cedar/processing/ElementDeclaration.h>

void pluginDeclaration(cedar::aux::PluginDeclarationListPtr plugin)
{
    cedar::proc::ElementDeclarationPtr summation_decl
    (
        new cedar::proc::ElementDeclarationTemplate <EarSubscriber>("Utilities")
    );
    plugin->add(summation_decl);
}
