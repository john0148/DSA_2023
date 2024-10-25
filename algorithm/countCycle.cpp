bool visited[MAXN];
bool on_stack[MAXN];
int number_of_cycles = 0;
int next_node[MAXN];

void dfs(int n) {
	visited[n] = on_stack[n] = true;
	int u = next_node[n];
	if (on_stack[u]) {
		number_of_cycles++;
	} else if (!visited[u]) {
		dfs(u);
	}
	on_stack[n] = false;
}

int main() {
	// read input, etc
	for (int i = 1; i <= N; i++) {
		if (!visited[i]) { dfs(i); }
	}
}