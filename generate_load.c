#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

long parse_env_var(char *string);
struct load_values* read_env_vars();
void run_test(struct load_values *test_data);
void perform_iteration(int megabytes, int duration);

struct load_values {
	long load_megabytes;
	long load_duration_seconds;
	long seconds_between_loads;

	long megabytes_increase_per_load;
	long seconds_increase_per_load;
	long total_test_duration_seconds;
};

/**
 * Env vars required:
 * 	LOAD_MEGABYTES
 * 	MEGABYTES_INCREASE_PER_LOAD
 * 	LOAD_DURATION_SECONDS
 * 	SECONDS_BETWEEN_LOADS
 * 	SECONDS_INCREASE_PER_LOAD
 * 	TOTAL_TEST_DURATION_SECONDS
 */
int main()
{
	struct load_values *test_data = read_env_vars();
	run_test(test_data);
	return 0;
}

void run_test(struct load_values *test_data)
{
	time_t start_t, current_t;
	int should_finish = 1;
	time(&start_t);

	while(should_finish != 0) {
		time(&current_t);
		// Stop if the time limit has been reached
		if(difftime(current_t, start_t) >= (double)test_data->total_test_duration_seconds)
		{
			printf("Finishing test!\n");
			should_finish = 0;
		}
		else
		{
			perform_iteration(test_data->load_megabytes, test_data->load_duration_seconds);
			// Increase the load MB and time
			test_data->load_megabytes += test_data->megabytes_increase_per_load;
			test_data->load_duration_seconds += test_data->seconds_increase_per_load;
			printf("Sleeping %lu seconds\n", test_data->seconds_between_loads);
			sleep(test_data->seconds_between_loads);
		}
	}

}

void perform_iteration(int megabytes, int duration)
{
	printf("Reserving %liMiB for %li seconds\n", megabytes, duration);
	// Load test_data megabytes
	void *useless_space = 
		malloc(megabytes*1048576);
	sleep(duration);
	free(useless_space);
}

struct load_values* read_env_vars()
{
	// Get env variables
	char* env_load_megabytes = getenv("LOAD_MEGABYTES");
	char* env_megabytes_increase_per_load = getenv("MEGABYTES_INCREASE_PER_LOAD");
	char* env_load_duration_seconds = getenv("LOAD_DURATION_SECONDS");
	char* env_seconds_between_loads = getenv("SECONDS_BETWEEN_LOADS");
	char* env_seconds_increase_per_load = getenv("SECONDS_INCREASE_PER_LOAD");
	char* env_total_test_duration_seconds = getenv("TOTAL_TEST_DURATION_SECONDS");

	struct load_values *values = malloc(sizeof(struct load_values));
	// Parse env variables to int
	values->load_megabytes = parse_env_var(env_load_megabytes);

	values->megabytes_increase_per_load =
		parse_env_var(env_megabytes_increase_per_load);

	values->load_duration_seconds =
		parse_env_var(env_load_duration_seconds);

	values->seconds_between_loads =
		parse_env_var(env_seconds_between_loads);
	
	values->total_test_duration_seconds =
		parse_env_var(env_total_test_duration_seconds);

	values->seconds_increase_per_load =
		parse_env_var(env_seconds_increase_per_load);

	return values;
}

long parse_env_var(char *string)
{
	// If we receive a null string, we consider it as 0
	if(string == NULL)
	{
		return 0;
	}

	// Converting the string to int
	char *end;
	long value;
	value = strtol(string, &end, 10);
	return value;
}
