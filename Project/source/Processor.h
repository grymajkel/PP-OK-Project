#pragma once
#include <iomanip>
#include <ostream>
#include <vector>

struct Process {
	Process() = default;
	Process(size_t ID, size_t length) : ID(ID), length(length) {}

	bool operator==(const Process& other) {
		return this->ID == other.ID;
	}

	size_t ID = SIZE_MAX;
	size_t length = 0;
};

class Core {
public:
	Core() = default;
	Core(const std::vector<Process>& processes) : processes(processes) { CalculateTotalLength(); }
	Core(size_t totalLength, const std::vector<Process>& processes) 
		: totalLength(totalLength), processes(processes) {}

	void Init(size_t totalLength, const std::vector<Process>& processes);
	void AppendNewProcess(Process process);
	void EraseProcess(size_t ID);
	size_t GetTotalLength() const { return totalLength; }
	Process GetProcess(size_t ID);
	const std::vector<Process>& GetProcesses() const { return std::ref(processes); }
	
	friend std::ostream& operator<<(std::ostream& os, const Core& core);

private:
	void CalculateTotalLength();

private:
	size_t totalLength = 0;
	std::vector<Process> processes = {};
};

class Processor
{
public:
	Processor(size_t N, const std::vector<size_t>& lengths) { Init(N, lengths); }
	void Init(size_t N, const std::vector<size_t>& lengths);
	const Core& GetCore(size_t ID) const;
	size_t FindCMax();

	friend std::ostream& operator<<(std::ostream& os, const Processor& processor);

private:
	size_t FindLeastUsedCore();

private:
	size_t N = 0;
	std::vector<Core> cores = {};
};
