/*
 *  client_report_control.c
 *
 *  Implementation of the ClientReportControlBlock class
 *
 *  Copyright 2014 Michael Zillgith
 *
 *  This file is part of libIEC61850.
 *
 *  libIEC61850 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  libIEC61850 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See COPYING file for the complete license text.
 */

#include "iec61850_client.h"

#include "stack_config.h"

#include "ied_connection_private.h"

#include "mms_mapping.h"

struct sClientGooseControlBlock {
    char* objectReference;
    MmsValue* goEna;
    MmsValue* goID;
    MmsValue* datSet;
    MmsValue* confRev;
    MmsValue* ndsCom;
    MmsValue* dstAddress;
    MmsValue* minTime;
    MmsValue* maxTime;
    MmsValue* fixedOffs;
};

ClientGooseControlBlock
ClientGooseControlBlock_create(char* objectReference)
{
    ClientGooseControlBlock self = (ClientGooseControlBlock) calloc(1, sizeof(struct sClientGooseControlBlock));

    self->objectReference = copyString(objectReference);

    return self;
}

void
ClientGooseControlBlock_destroy(ClientGooseControlBlock self)
{
    free(self->objectReference);

    MmsValue_deleteIfNotNull(self->goEna);
    MmsValue_deleteIfNotNull(self->goID);
    MmsValue_deleteIfNotNull(self->datSet);
    MmsValue_deleteIfNotNull(self->confRev);
    MmsValue_deleteIfNotNull(self->ndsCom);
    MmsValue_deleteIfNotNull(self->dstAddress);
    MmsValue_deleteIfNotNull(self->minTime);
    MmsValue_deleteIfNotNull(self->maxTime);
    MmsValue_deleteIfNotNull(self->fixedOffs);

    free(self);
}

bool
ClientGooseControlBlock_getGoEna(ClientGooseControlBlock self)
{
    if (self->goEna != NULL)
        return MmsValue_getBoolean(self->goEna);
    else
        return false;
}

void
ClientGooseControlBlock_setGoEna(ClientGooseControlBlock self, bool goEna)
{
    if (self->goEna == NULL)
        self->goEna = MmsValue_newBoolean(goEna);
    else
        MmsValue_setBoolean(self->goEna, goEna);
}

char*
ClientGooseControlBlock_getGoID(ClientGooseControlBlock self)
{
    if (self->goID != NULL)
        return MmsValue_toString(self->goID);
    else
        return NULL;
}

void
ClientGooseControlBlock_setGoID(ClientGooseControlBlock self, char* goID)
{
    if (self->goID == NULL)
        self->goID = MmsValue_newVisibleString(goID);
    else
        MmsValue_setVisibleString(self->goID, goID);
}

char*
ClientGooseControlBlock_getDatSet(ClientGooseControlBlock self)
{
    if (self->datSet != NULL)
        return MmsValue_toString(self->datSet);
    else
        return NULL;
}

void
ClientGooseControlBlock_setDatSet(ClientGooseControlBlock self, char* datSet)
{
    if (self->datSet == NULL)
        self->datSet = MmsValue_newVisibleString(datSet);
    else
        MmsValue_setVisibleString(self->datSet, datSet);
}

uint32_t
ClientGooseControlBlock_getConfRev(ClientGooseControlBlock self)
{
    if (self->confRev != NULL)
        return MmsValue_toUint32(self->confRev);
    else
        return 0;
}

bool
ClientGooseControlBlock_getNdsComm(ClientGooseControlBlock self)
{
    if (self->ndsCom != NULL)
        return MmsValue_getBoolean(self->ndsCom);
    else
        return false;
}

uint32_t
ClientGooseControlBlock_getMinTime(ClientGooseControlBlock self)
{
    if (self->minTime != NULL)
        return MmsValue_toUint32(self->minTime);
    else
        return 0;
}

uint32_t
ClientGooseControlBlock_getMaxTime(ClientGooseControlBlock self)
{
    if (self->maxTime != NULL)
        return MmsValue_toUint32(self->maxTime);
    else
        return 0;
}

bool
ClientGooseControlBlock_getFixedOffs(ClientGooseControlBlock self)
{
    if (self->fixedOffs != NULL)
        return MmsValue_getBoolean(self->fixedOffs);
    else
        return false;
}

static MmsValue*
newEmptyPhyCommAddress(void) {
    MmsValue* self = MmsValue_createEmptyStructure(4);

    MmsValue_setElement(self, 0, MmsValue_newOctetString(6, 6));
    MmsValue_setElement(self, 1, MmsValue_newUnsigned(8));
    MmsValue_setElement(self, 2, MmsValue_newUnsigned(16));
    MmsValue_setElement(self, 3, MmsValue_newUnsigned(16));

    return self;
}

MmsValue*
ClientGooseControlBlock_getDstAddress_addr(ClientGooseControlBlock self)
{
    if (self->dstAddress != NULL)
        return MmsValue_getElement(self->dstAddress, 0);
    else
        return NULL;
}

void
ClientGooseControlBlock_setDstAddress_addr(ClientGooseControlBlock self, MmsValue* macAddr)
{
    if (self->dstAddress == NULL)
        self->dstAddress = newEmptyPhyCommAddress();

    MmsValue* addr = MmsValue_getElement(self->dstAddress, 0);
    MmsValue_update(addr, macAddr);
}

uint8_t
ClientGooseControlBlock_getDstAddress_priority(ClientGooseControlBlock self)
{
    if (self->dstAddress != NULL)
        return (uint8_t) MmsValue_toUint32(MmsValue_getElement(self->dstAddress, 1));
    else
        return 0;
}

void
ClientGooseControlBlock_setDstAddress_priority(ClientGooseControlBlock self, uint8_t priorityValue)
{
    if (self->dstAddress != NULL)
        self->dstAddress = newEmptyPhyCommAddress();

    MmsValue* priority = MmsValue_getElement(self->dstAddress, 1);
    MmsValue_setUint8(priority, priorityValue);
}

uint16_t
ClientGooseControlBlock_getDstAddress_vid(ClientGooseControlBlock self)
{
    if (self->dstAddress != NULL)
        return (uint16_t) MmsValue_toUint32(MmsValue_getElement(self->dstAddress, 2));
    else
        return 0;
}

void
ClientGooseControlBlock_setDstAddress_vid(ClientGooseControlBlock self, uint16_t vidValue)
{
    if (self->dstAddress != NULL)
        self->dstAddress = newEmptyPhyCommAddress();

    MmsValue* vid = MmsValue_getElement(self->dstAddress, 2);
    MmsValue_setUint8(vid, vidValue);
}

uint16_t
ClientGooseControlBlock_getDstAddress_appid(ClientGooseControlBlock self)
{
    if (self->dstAddress != NULL)
        return (uint16_t) MmsValue_toUint32(MmsValue_getElement(self->dstAddress, 3));
    else
        return 0;
}

void
ClientGooseControlBlock_setDstAddress_appid(ClientGooseControlBlock self, uint16_t appidValue)
{
    if (self->dstAddress != NULL)
        self->dstAddress = newEmptyPhyCommAddress();

    MmsValue* appid = MmsValue_getElement(self->dstAddress, 3);
    MmsValue_setUint8(appid, appidValue);
}

static void
updateOrClone(MmsValue** valuePtr, MmsValue* values, int index)
{
    if (*valuePtr != NULL)
        MmsValue_update(*valuePtr, MmsValue_getElement(values, index));
    else
        *valuePtr = MmsValue_clone(MmsValue_getElement(values, index));
}

static bool
private_ClientGooseControlBlock_updateValues(ClientGooseControlBlock self, MmsValue* values)
{
    updateOrClone(&(self->goEna), values, 0);
    updateOrClone(&(self->goID), values, 1);
    updateOrClone(&(self->datSet), values, 2);
    updateOrClone(&(self->confRev), values, 3);
    updateOrClone(&(self->ndsCom), values, 4);
    updateOrClone(&(self->dstAddress), values, 5);
    updateOrClone(&(self->minTime), values, 6);
    updateOrClone(&(self->maxTime), values, 7);
    updateOrClone(&(self->fixedOffs), values, 8);

    return true;
}

ClientGooseControlBlock
IedConnection_getGoCBValues(IedConnection self, IedClientError* error, char* goCBReference, ClientGooseControlBlock updateGoCB)
{
    MmsError mmsError = MMS_ERROR_NONE;
    *error = IED_ERROR_OK;

    ClientGooseControlBlock returnGoCB = updateGoCB;

    char domainId[65];
    char itemId[129];

    MmsMapping_getMmsDomainFromObjectReference(goCBReference, domainId);

    char* itemIdStart = goCBReference + strlen(domainId) + 1;

    char* separator = strchr(itemIdStart, '.');

    if (separator == NULL) {
        *error = IED_ERROR_OBJECT_REFERENCE_INVALID;
        return NULL;
    }

    int separatorOffset = separator - itemIdStart;

    memcpy(itemId, itemIdStart, separatorOffset);

    itemId[separatorOffset] = '$';
    itemId[separatorOffset + 1] = 'G';
    itemId[separatorOffset + 2] = 'O';
    itemId[separatorOffset + 3] = '$';

    strcpy(itemId + separatorOffset + 4, separator + 1);

    if (DEBUG_IED_CLIENT)
        printf("DEBUG_IED_CLIENT: getGoCBValues for %s\n", goCBReference);

    MmsValue* goCB = MmsConnection_readVariable(self->connection, &mmsError, domainId, itemId);

    if (mmsError != MMS_ERROR_NONE) {
        *error = iedConnection_mapMmsErrorToIedError(mmsError);

        return NULL;
    }

    if (goCB == NULL) {
        *error = IED_ERROR_OBJECT_DOES_NOT_EXIST;
        return NULL;
    }

    if (MmsValue_getType(goCB) != MMS_STRUCTURE) {
        if (DEBUG_IED_CLIENT)
            printf("DEBUG_IED_CLIENT: getRCBValues returned wrong type!\n");

        MmsValue_delete(goCB);

        *error = IED_ERROR_UNKNOWN;
        return NULL;
    }

    if (returnGoCB == NULL)
        returnGoCB = ClientGooseControlBlock_create(goCBReference);

    private_ClientGooseControlBlock_updateValues(returnGoCB, goCB);

    MmsValue_delete(goCB);

    *error = IED_ERROR_OK;

    return returnGoCB;
}

void
IedConnection_setGoCBValues(IedConnection self, IedClientError* error, ClientGooseControlBlock goCB,
        uint32_t parametersMask, bool singleRequest)
{
    *error = IED_ERROR_OK;

    MmsError mmsError = MMS_ERROR_NONE;

    char domainId[65];
    char itemId[129];

    MmsMapping_getMmsDomainFromObjectReference(goCB->objectReference, domainId);

    char* itemIdStart = goCB->objectReference + strlen(domainId) + 1;

    char* separator = strchr(itemIdStart, '.');

    if (separator == NULL) {
        *error = IED_ERROR_OBJECT_REFERENCE_INVALID;
        return;
    }

    int separatorOffset = separator - itemIdStart;

    memcpy(itemId, itemIdStart, separatorOffset);

    itemId[separatorOffset] = '$';
    itemId[separatorOffset + 1] = 'G';
    itemId[separatorOffset + 2] = 'O';
    itemId[separatorOffset + 3] = '$';

    strcpy(itemId + separatorOffset + 4, separator + 1);

    if (DEBUG_IED_CLIENT)
        printf("DEBUG_IED_CLIENT: setGoCBValues for %s\n", goCB->objectReference);

    int itemIdLen = strlen(itemId);

    /* create the list of requested itemIds references */
    LinkedList itemIds = LinkedList_create();
    LinkedList values = LinkedList_create();

    /* add rGoEna as last element */
    if (parametersMask & GOCB_ELEMENT_GO_ID) {
        strcpy(itemId + itemIdLen, "$GoID");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->goID);
    }

    if (parametersMask & GOCB_ELEMENT_DATSET) {
        strcpy(itemId + itemIdLen, "$DatSet");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->datSet);
    }

    if (parametersMask & GOCB_ELEMENT_CONF_REV) {
        strcpy(itemId + itemIdLen, "$ConfRev");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->confRev);
    }

    if (parametersMask & GOCB_ELEMENT_NDS_COMM) {
        strcpy(itemId + itemIdLen, "$NdsCom");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->ndsCom);
    }

    if (parametersMask & GOCB_ELEMENT_DST_ADDRESS) {
        strcpy(itemId + itemIdLen, "$DstAddress");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->dstAddress);
    }

    if (parametersMask & GOCB_ELEMENT_MIN_TIME) {
        strcpy(itemId + itemIdLen, "$MinTime");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->minTime);
    }

    if (parametersMask & GOCB_ELEMENT_MAX_TIME) {
        strcpy(itemId + itemIdLen, "$MaxTime");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->maxTime);
    }

    if (parametersMask & GOCB_ELEMENT_FIXED_OFFS) {
        strcpy(itemId + itemIdLen, "$FixedOffs");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->fixedOffs);
    }


    if (parametersMask & GOCB_ELEMENT_GO_ENA) {
        strcpy(itemId + itemIdLen, "$GoEna");

        LinkedList_add(itemIds, copyString(itemId));
        LinkedList_add(values, goCB->goEna);
    }

    if (singleRequest) {
        LinkedList accessResults = NULL;

        MmsConnection_writeMultipleVariables(self->connection, &mmsError, domainId, itemIds, values, &accessResults);

        if (accessResults != NULL) {
            LinkedList element = LinkedList_getNext(accessResults);

            while (element != NULL) {
                MmsValue* accessResult = (MmsValue*) element->data;

                if (MmsValue_getDataAccessError(accessResult) != DATA_ACCESS_ERROR_SUCCESS) {
                    mmsError = MMS_ERROR_ACCESS_OBJECT_NON_EXISTENT;
                    break;
                }

                element = LinkedList_getNext(element);
            }

            LinkedList_destroyDeep(accessResults, (LinkedListValueDeleteFunction) MmsValue_delete);
        }

        *error = iedConnection_mapMmsErrorToIedError(mmsError);
        goto exit_function;
    }
    else {
        LinkedList itemIdElement = LinkedList_getNext(itemIds);
        LinkedList valueElement = LinkedList_getNext(values);

        while (itemIdElement != NULL) {
            char* rcbItemId = (char*) itemIdElement->data;
            MmsValue* value = (MmsValue*) valueElement->data;

            MmsConnection_writeVariable(self->connection, &mmsError, domainId, rcbItemId, value);

            if (mmsError != MMS_ERROR_NONE)
                break;

            itemIdElement = LinkedList_getNext(itemIdElement);
            valueElement = LinkedList_getNext(valueElement);
        }

        *error = iedConnection_mapMmsErrorToIedError(mmsError);
        goto exit_function;
    }

exit_function:
    LinkedList_destroy(itemIds);
    LinkedList_destroyStatic(values);
}

