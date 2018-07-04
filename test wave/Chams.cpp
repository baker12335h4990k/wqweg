/*credits by ibanned*/

#include "Chams.h"
#include "offsets.h"
#include "SDK.h"
#include "Interfaces.h"





void InitKeyValues(KeyValues* keyValues, char* name)
{

	DWORD dwFunction = (DWORD)Offsets::Functions::KeyValues_KeyValues;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{

	DWORD dwFunction = (DWORD)Offsets::Functions::KeyValues_LoadFromBuffer;

	__asm
	{
		push 0
		push 0
		push 0
		push pBuffer
		push resourceName
		mov ecx, keyValues
		call dwFunction
	}
}

IMaterial* CreateMaterial(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces::MaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}



void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{

	if (useColor)
	{
		float temp[3] =
		{

			color.r(),
			color.g(),
			color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = color.a();

		Interfaces::RenderView->SetBlend(1.0f);
		Interfaces::RenderView->SetColorModulation(temp);
	}

	if (forceMaterial)
		Interfaces::ModelRender->ForcedMaterialOverride(material);
	else
		Interfaces::ModelRender->ForcedMaterialOverride(NULL);

}