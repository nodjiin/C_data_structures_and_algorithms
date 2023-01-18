#ifndef DATATYPE
#define DATATYPE

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	typedef int data_type;
	typedef int(*data_type_compare_fn)(const data_type a, const data_type b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !DATATYPE
