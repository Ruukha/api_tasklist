#pragma once

bool getPayload(StaticJsonDocument<4096> &doc);
void get_last_update(time_t &last_update);
bool get_task_by_id(StaticJsonDocument<1024> &task, const char* id);
bool remove_task_id(const char* id);