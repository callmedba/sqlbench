#ifndef DBC_H
#define DBC_H
#include <getopt.h>
#include "db.h"

struct dbc_sql_operation_t
{
	struct db_context_t * (*db_init)(void);
	int (*connect_to_db)(struct db_context_t *dbc);
	int (*disconnect_from_db)(struct db_context_t *dbc);
	int (*commit_transaction)(struct db_context_t *dbc);
	int (*rollback_transaction)(struct db_context_t *dbc);
	int (*sql_execute)(struct db_context_t *dbc, char * query, struct sql_result_t * sql_result,
                       char * query_name);
	int (*sql_fetchrow)(struct db_context_t *dbc, struct sql_result_t * sql_result);
	int (*sql_close_cursor)(struct db_context_t *dbc, struct sql_result_t * sql_result);
	char *(*sql_getvalue)(struct db_context_t *dbc, struct sql_result_t * sql_result, int field);
};

struct dbc_info_t
{
	char * dbc_name;
	char * dbc_usage;
	struct dbc_sql_operation_t *dbc_sql_operation;
	struct option *(*dbc_get_options)();
	int (*dbc_set_option)(const char *optname, const char *optvalue);
	/* DBMS special features */
	int is_forupdate_supported; /* sqlite not support */
};

struct dbc_construct_t
{
	int (*dbc_init)();
};

/* configuations */
extern int _is_forupdate_supported;

extern struct dbc_info_t *make_dbc_info(const char *dbcname, const char *dbcusage);
extern void init_dbc_manager();
extern void dbc_manager_add(struct dbc_info_t *dbc_info);
extern const char * dbc_manager_get_dbcnames();
extern const char * dbc_manager_get_dbcusages();
extern int dbc_manager_set(char *dbcname);
extern struct option * dbc_manager_get_dbcoptions();
extern int dbc_manager_set_dbcoption(const char *optname, const char *optvalue);

extern struct db_context_t *dbc_db_init(void);
extern int dbc_connect_to_db(struct db_context_t *dbc);
extern int dbc_disconnect_from_db(struct db_context_t *dbc);
extern int dbc_commit_transaction(struct db_context_t *dbc);
extern int dbc_rollback_transaction(struct db_context_t *dbc);
extern int dbc_sql_execute(struct db_context_t *dbc, char * query, struct sql_result_t * sql_result,
 					char * query_name);
extern int dbc_sql_fetchrow(struct db_context_t *dbc, struct sql_result_t * sql_result);
extern int dbc_sql_close_cursor(struct db_context_t *dbc, struct sql_result_t * sql_result);
extern char * dbc_sql_getvalue(struct db_context_t *dbc, struct sql_result_t * sql_result, int field);

#endif