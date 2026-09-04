#include "Effect2/hh_effect_object_def.h"

extern /* static */ Object_Class _pObject_Class_List[48];
extern /* static */ MemoryPool_AssociationInfomeation _MemoryPool_AssociationInfo_Table[48];
extern /* static */ u_int _Object_Class_Priority_List[49];
extern /* static */ int _AutoPost_Association_List[2][18];
extern Object_Instance* _pHierarchyTable[48];
extern Object_Instance _Object_instance_table[600];
extern Object_DataPool_Infomeation _Object_Data_Table[48];
extern ImpactQueue_Element _Queue[500];
extern Object_Group_Infomeation _Object_Group_Info[1];

u_int MemoryPool_AllRelease(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max) {
    u_int i, result;
    Object_DataPool_Infomeation *pPool_Info;
    Object_DataPool_Infomeation DataInfo_NULL;

    memset(&DataInfo_NULL, 0, sizeof(Object_DataPool_Infomeation));
    for(i = 0; i < Class_Kind_Max; i++) {
        pPool_Info = pPool_Info_Table + i;
        *pPool_Info = DataInfo_NULL;
    }
    return 1;
}

u_int MemoryPool_Inspect_and_Allocate(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max) {
    u_int i, j;
    u_int result = 0;
    MemoryPool_AssociationInfomeation* pAssoci_Info;
    Object_DataPool_Infomeation* pPool_Info;
    u_int Base; // r30
    u_int End; // r2
    int room_name;
    void* pAddress;


    pAddress = HH_MemoryManager_AllocateMemoryBlock_Get(1);
    Base = (u_int)pAddress;

    for (i = 0; i < Class_Kind_Max; i++) {
        pAssoci_Info = &pAssoci_Info_Table[i];
        pPool_Info = &pPool_Info_Table[i];

        if (pAssoci_Info->Existent)
            switch (pAssoci_Info->Existent) {                          /* irregular */
                case 1:
                    *pPool_Info = pAssoci_Info->DataPool_Info;
                    if (pPool_Info->pBlock_Table == NULL) {
                        pPool_Info->pBlock_Table = pAddress;
                        pAddress = HH_MemoryManager_DesignateSize_Alignment16Address_Calculator(pAddress, pPool_Info->Block_Size, pPool_Info->Block_Index_Max);
                    }
                    result = 1;
                    break;
                case 2:
                    room_name = RoomNameJms();
                    for (j = 0; j < pAssoci_Info->LinkList_Max; j++) {
                        if (room_name == pAssoci_Info->pLinkList[j]) {
                            *pPool_Info = pAssoci_Info->DataPool_Info;
                            pPool_Info->pBlock_Table = pAddress;
                            pAddress = HH_MemoryManager_DesignateSize_Alignment16Address_Calculator(pAddress, pPool_Info->Block_Size, pPool_Info->Block_Index_Max);

                            result = 1;
                            break;
                        }
                    }
            }
    }
    End = (u_int)pAddress;
    printf("Object Work Allocate Size = %d kB\n\0", (End - Base) >> 10);
    return result;
}


u_int MemoryPool_AllClear(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max) {
    Object_DataPool_Infomeation* pPool_Info;
    u_int i, result;

    result = 0;
    for(i = 0; i < Class_Kind_Max; ++i) {
        pPool_Info = pPool_Info_Table + i;
        if (pPool_Info->pBlock_Table != NULL) {
            memset(pPool_Info_Table[i].pBlock_Table,
                   0,
                   pPool_Info_Table[i].Block_Size * pPool_Info_Table[i].Block_Index_Max);
            result = 1;
        }
    }
    return result;
}

u_int MemoryPool_Controller(Object_DataPool_Infomeation* pPool_Info_Table, MemoryPool_AssociationInfomeation* pAssoci_Info_Table, u_int Class_Kind_Max) {
    u32 result;

    result = 0;
    if (HH_MemoryManager_AllocateMemoryBlock_Check(1) != 0) {
        result = 1;
        result *= MemoryPool_AllRelease(pPool_Info_Table, pAssoci_Info_Table, Class_Kind_Max);
        result *= MemoryPool_Inspect_and_Allocate(pPool_Info_Table, pAssoci_Info_Table, Class_Kind_Max);
        result *= MemoryPool_AllClear(pPool_Info_Table, pAssoci_Info_Table, Class_Kind_Max);
    }
    return result;
}

static void Effect_Object_Initialize(void) {
    Object_Group_Infomeation* pInfo;

    pInfo = HH_Effect_Object_Infomeation_Get();
    Object_Group_Infomeation_Set(pInfo);
    Object_Group_QueueInfomeation_Set(pInfo, &_Queue, 500);
    Object_Group_ClassAssociationInfomeation_Set(pInfo, &_pObject_Class_List, &_Object_Data_Table, &_Object_Class_Priority_List, CLASS_DESCRIPTOR_MAX);
    Object_Group_InstanceTableInfomeation_Set(pInfo, &_Object_instance_table, &_pHierarchyTable, 600);
    Object_Group_All_Initialize(pInfo);
}

void HH_Effect_Object_Impact_Post(ImpactQueue_Element* pElement) {
    ImpactDescriptor_Post(HH_Effect_Object_Infomeation_Get(), pElement);
}

void HH_Effect_Object_DesignateClassInstance_Clear(u_int Class_Descriptor) {
    Object_Group_InstanceTable_DesignateClassDescriptorAttach_Initialize(HH_Effect_Object_Infomeation_Get(), Class_Descriptor);
}

void HH_Effect_Object_DesignateHandleInstance_Clear(u_int hInstance) {
    Object_Group_InstanceTable_DesignateInstanceHandleAttach_Initialize(HH_Effect_Object_Infomeation_Get(), hInstance);
}

Object_Group_Infomeation* HH_Effect_Object_Infomeation_Get(void) {
    return &_Object_Group_Info;
}

void HH_Effect_Object_Manager(void) {
    Object_Group_Manager(HH_Effect_Object_Infomeation_Get());
    shPadTrigger(0, PAD_KEY_CROSS);
    shPadTrigger(0, PAD_KEY_R2);
}

u_int HH_Effect_Object_MemoryBlock_Allocate(void) {
    u_int ret;

    ret = 0;
    if (MemoryPool_Controller(&_Object_Data_Table, &_MemoryPool_AssociationInfo_Table, 48)) {
        Effect_Object_Initialize();
        ret = 1;
    }
    return ret;
}

// thanks: MrCoolTheCucumber
void HH_Effect_Object_AutoPost(void) {
    ImpactQueue_Element descriptor;
    u_int i;
    int room_name;

    room_name = RoomNameJms();

    for (i = 0; i < 18; i++) {
        if (_AutoPost_Association_List[0][i * 2] == room_name) {
            descriptor.Class_Descriptor = _AutoPost_Association_List[0][i * 2 + 1];
            descriptor.hInstance = 0;
            descriptor.pResultHandle_Address = 0;
            ImpactDescriptor_Post(&_Object_Group_Info, &descriptor);
        }
    }
}
