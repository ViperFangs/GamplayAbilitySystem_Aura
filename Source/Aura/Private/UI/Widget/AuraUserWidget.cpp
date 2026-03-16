// Copyright VQHQ


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(class UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	/* Call the blueprintable callable function 
	 * Example: This function can be used to get the health variable from the model as soon as the Widget is set.
	 */
	WidgetControllerSet();
}
