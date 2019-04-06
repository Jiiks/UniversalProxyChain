Usage

Put in game dir, throw whatever extra dll's you want to load in `uclib` directory.

You can add a post attach function to your extra dll:

```
extern "C" {
    int __declspec(dllexport) __stdcall postAttach() {
        // Do whatever post attach
        return 0;
    }
}
```
