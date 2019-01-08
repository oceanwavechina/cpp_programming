/*
 * aws4_signature.cpp
 *
 *  Created on: Apr 14, 2017
 *      Author: liuyanan
 */

#include <iostream>
#include <string>
#include <ctime>
#include <map>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <curl/curl.h>

using namespace std;


void Sign( unsigned char* key, int keyLength, unsigned char* input, int inputLength, unsigned char* output )
{
	uint32_t output_len;

	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);
	HMAC_Init_ex(&ctx, key, keyLength, EVP_sha256(), NULL);
	HMAC_Update(&ctx, input, inputLength);
	HMAC_Final(&ctx, output, &output_len);
	HMAC_CTX_cleanup(&ctx);
}

string HmacString(unsigned char* signingKey, string stringToSign) {

	unsigned char hash[SHA256_DIGEST_LENGTH];
	char outputBuffer[SHA256_DIGEST_LENGTH*2 + 1];

	Sign( signingKey, SHA256_DIGEST_LENGTH, (unsigned char*)stringToSign.c_str(), stringToSign.length(), hash );

	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[SHA256_DIGEST_LENGTH*2] = 0;

	return string(outputBuffer);
}

void getSignatureKey(string key, string dateStamp, string regionName, string serviceName, unsigned char* output) {

	string aws4Reuqest = "aws4_request";
	string awsKey = string("AWS4") + key;

	Sign((unsigned char*)awsKey.c_str(), awsKey.length(), (unsigned char*)dateStamp.c_str(), dateStamp.length(), output);
	Sign(output, SHA256_DIGEST_LENGTH, (unsigned char*)regionName.c_str(), regionName.length(), output);
	Sign(output, SHA256_DIGEST_LENGTH, (unsigned char*)serviceName.c_str(), serviceName.length(), output);
	Sign(output, SHA256_DIGEST_LENGTH, (unsigned char*)aws4Reuqest.c_str(), aws4Reuqest.length(), output);
}

void DateAndStamp(string& date, string& stamp) {
	time_t t = std::time(NULL);

	char mbstr[64];
	if (std::strftime(mbstr, sizeof(mbstr), "%Y%m%dT%H%M%SZ", std::localtime(&t))) {
		date = mbstr;
	}

	memset(mbstr, 0, 64);
	if (std::strftime(mbstr, sizeof(mbstr), "%Y%m%d", std::localtime(&t))) {
		stamp = mbstr;
	}
}

string SHA256String(string data) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	char outputBuffer[SHA256_DIGEST_LENGTH*2 + 1];

	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, data.c_str(), data.length());
	SHA256_Final(hash, &sha256);

	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}
	outputBuffer[SHA256_DIGEST_LENGTH*2] = 0;

	return string(outputBuffer);
}

static size_t process_data(void *data, size_t size, size_t nmemb, string &content)
{
    long sizes = size * nmemb;
    string temp;
    temp = string((char*)data,sizes);
    content += temp;
    return sizes;
}

string HttpGet(string url, map<string, string> headers_map) {
	CURL *curl;
	CURLcode res;
	string result;
	struct curl_slist *headers = NULL;
	for(map<string, string>::iterator it= headers_map.begin(); it != headers_map.end(); ++it) {
		headers = curl_slist_append(headers, (it->first+":"+it->second).c_str());
	}

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL,url.c_str());
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			 cerr << "curl_easy_perform() failed:" << curl_easy_strerror(res) << endl;
		curl_slist_free_all(headers);
		curl_easy_cleanup(curl);
	}

	return result;
}

string HttpPost(string url, map<string, string> headers_map, string body) {
	CURL *curl;
	CURLcode res;
	string result;
	struct curl_slist *headers = NULL;
	for(map<string, string>::iterator it= headers_map.begin(); it != headers_map.end(); ++it) {
		headers = curl_slist_append(headers, (it->first+":"+it->second).c_str());
	}

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &process_data);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}

	return result;
}


struct KSYN_PARAM {
	string endpoint;
	string method;
	string canonical_uri;
	string request_parameters;
	string x_action;
	string x_version;
};


string AWS4Request(KSYN_PARAM& kysn_param) {

	string access_key = "AKLTQO2NFIycTBmqbGq7RtWUbA";
	string secret_key = "ONtw9J+C7S3FlEbXg/izIkUZ62Obv1zxEeeh6+ONMVrHNyy2v1ndbCTjE7KFMJ9hxw==";
	string host = "kls.api.ksyun.com";
	string service = "kls";
	string region = "cn-beijing-6";


	string& endpoint = kysn_param.endpoint;
	string& method = kysn_param.method;
	string& canonical_uri = kysn_param.canonical_uri;
	string& request_parameters = kysn_param.request_parameters;
	map<string, string> headers;
	headers.insert(map<string, string>::value_type("x-action", kysn_param.x_action));
	headers.insert(map<string, string>::value_type("x-version", kysn_param.x_version));

	string awsDate;
	string awsDateStamp;
	DateAndStamp(awsDate, awsDateStamp);

	string canonical_headers = string("host:") + host + "\n" + "x-amz-date:" + awsDate + "\n";
	string signed_headers = "host;x-amz-date";

	string payload_hash;
	string canonical_querystring;

	if (method == "GET") {
		canonical_querystring = request_parameters;
		payload_hash = SHA256String("");
	} else {
		canonical_querystring = "";
		payload_hash = SHA256String(request_parameters);
	}

	string canonical_request = method + '\n' + canonical_uri + '\n' + canonical_querystring + '\n' + canonical_headers + '\n' + signed_headers + '\n' + payload_hash;

	string algorithm = "AWS4-HMAC-SHA256";
	string credential_scope = awsDateStamp + '/' + region + '/' + service + '/' + "aws4_request";
	string string_to_sign = algorithm + '\n' +  awsDate + '\n' +  credential_scope + '\n' +  SHA256String(canonical_request);

	unsigned char signing_key[SHA256_DIGEST_LENGTH];

	getSignatureKey(secret_key, awsDateStamp, region, service, signing_key);
	string signature = HmacString(signing_key, string_to_sign);
	string authorization_header = algorithm + ' ' + "Credential=" + access_key + '/' + credential_scope + ", " +  "SignedHeaders=" + signed_headers + ", " + "Signature=" + signature;


	headers.insert(map<string, string>::value_type("X-Amz-Date", awsDate));
	headers.insert(map<string, string>::value_type("Authorization", authorization_header));

    cout << "BEGIN REQUEST++++++++++++++++++++++++++++++++++++" << endl;
    if (method == "GET")
    	return HttpGet(endpoint + '?' + canonical_querystring, headers);
    else
    	return HttpPost(endpoint + '?' + canonical_querystring, headers, request_parameters);
}


int main()
{
	KSYN_PARAM listRecordingTasks;
	listRecordingTasks.endpoint = "http://kls.api.ksyun.com/api/ListRecordingTasks/2017-01-01";
	listRecordingTasks.method = "GET";
	listRecordingTasks.canonical_uri = "/api/ListRecordingTasks/2017-01-01";
	listRecordingTasks.request_parameters = "App=voicelive&OrderTime=1&Pubdomain=push.ksyun.kuwo.cn&RecType=2&Stream=199820093&UniqueName=jxtest";
	listRecordingTasks.x_action = "ListRecordingTasks";
	listRecordingTasks.x_version = "2017-01-01";


	KSYN_PARAM startStreamRecord;
	startStreamRecord.endpoint = "http://kls.api.ksyun.com/api/StartStreamRecord/2017-01-01";
	startStreamRecord.method = "POST";
	startStreamRecord.canonical_uri = "/api/StartStreamRecord/2017-01-01";
	startStreamRecord.request_parameters = "UniqueName=jxtest&App=voicelive&Pubdomain=push.ksyun.kuwo.cn&Stream=199820093&Mp4VodEnable=1";
	startStreamRecord.x_action = "StartStreamRecord";
	startStreamRecord.x_version = "2017-01-01";


	KSYN_PARAM stopStreamRecord;
	stopStreamRecord.endpoint = "http://kls.api.ksyun.com/api/StopStreamRecord/2017-01-01";
	stopStreamRecord.method = "POST";
	stopStreamRecord.canonical_uri = "/api/StopStreamRecord/2017-01-01";
	stopStreamRecord.request_parameters = "UniqueName=jxtest&App=voicelive&Pubdomain=push.ksyun.kuwo.cn&Stream=199820093&RecID=77";
	stopStreamRecord.x_action = "StopStreamRecord";
	stopStreamRecord.x_version = "2017-01-01";

	string result;
	result = AWS4Request(listRecordingTasks);
//	result = AWS4Request(startStreamRecord);
//	result = AWS4Request(stopStreamRecord);
	cout << "result:\n\t" << result << endl;

    return 0;
}
