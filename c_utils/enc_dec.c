int amf_nas_encode_tv(unsigned char* buffer, int length_buffer, int ie_length, unsigned char* ie_buffer, unsigned char ie_type, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_type);
	remaining_length -= 1;
	data += 1;

	if(remaining_length < ie_length) return AMF_FAILURE;

	memcpy(data, ie_buffer, ie_length);
	
	data += ie_length;
	remaining_length -= ie_length;

	return data - buffer;
}

int amf_nas_encode_lv(unsigned char* buffer, int length_buffer, int ie_length, unsigned char* ie_buffer, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_length);
	remaining_length -= 1;
	data += 1;

	if(remaining_length < ie_length) return AMF_FAILURE;

	memcpy(data, ie_buffer, ie_length);
	
	data += ie_length;
	remaining_length -= ie_length;

	return data - buffer;
}

int amf_nas_encode_lv_e(unsigned char* buffer, int length_buffer, int ie_length, unsigned char* ie_buffer, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	if(remaining_length < 2) return AMF_FAILURE;
	bufferAddUint2_linux(data, ie_length);
	remaining_length -= 2;
	data += 2;

	if(remaining_length < ie_length) return AMF_FAILURE;

	memcpy(data, ie_buffer, ie_length);
	
	data += ie_length;
	remaining_length -= ie_length;

	return data - buffer;
}

int amf_nas_encode_tlv(unsigned char* buffer, int length_buffer, int ie_length, unsigned char* ie_buffer, unsigned char ie_type, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_type);
	remaining_length -= 1;
	data += 1;

	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_length);
	remaining_length -= 1;
	data += 1;

	if(remaining_length < ie_length) return AMF_FAILURE;

	memcpy(data, ie_buffer, ie_length);
	
	data += ie_length;
	remaining_length -= ie_length;

	return data - buffer;
}

if(ie_struct->modified_ie & AMF_NAS_REG_REQ_LAST_VISITED_REG_TAI)
{
	ret = amf_nas_encode_tlv(data, remaining_length, ie_struct->length_last_visited_reg_tai, ie_struct->last_visited_reg_tai, AMF_NAS_REG_REQ_IEI_LAST_VISITED_REG_TAI, err_code);
	if(ret == AMF_FAILURE) return ret;
	data += ret;
	remaining_length -= ret;
}

int amf_nas_encode_tlv_e(unsigned char* buffer, int length_buffer, int ie_length, unsigned char* ie_buffer, unsigned char ie_type, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_type);
	remaining_length -= 1;
	data += 1;

	if(remaining_length < 2) return AMF_FAILURE;
	bufferAddUint2_linux(data, ie_length);
	remaining_length -= 2;
	data += 2;

	if(remaining_length < ie_length) return AMF_FAILURE;

	memcpy(data, ie_buffer, ie_length);
	
	data += ie_length;
	remaining_length -= ie_length;

	return data - buffer;
}

int amf_nas_encode_special_ie(unsigned char* buffer, int length_buffer, unsigned char ie_type, unsigned char ie_val, int* err_code)
{
	unsigned char* data = buffer;
	int remaining_length = length_buffer;

	ie_type <<= 4;
	ie_type |= ie_val;
	if(remaining_length < 1) return AMF_FAILURE;
	bufferAddUint1_linux(data, ie_val);
	remaining_length -= 1;
	data += 1;

	return data - buffer;
}
