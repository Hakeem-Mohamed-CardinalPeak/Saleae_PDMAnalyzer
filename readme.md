# Saleae PDM Analyzer
This analyzer is useful for PDM streams. It counts the number of 1s present on
the data line for a given clock's rising and falling edges.  Within the GUI left/right 
channel values are separated by commas, and when exported as CSV they are saved
as separate columns.

It does its best to start with the clock signal. However, it may be shifted
against the samples you receive in your code. Changing the bits per sample
configuration sample to 1 can make it easy to read individual bits instead of the
ones count for a set of bits.

# Python Scripts - smash_csv.py, handle_pdm.py
These scripts process the PDM data exported as CSV from Logic so that they can be imported into 
Audacity for analysis.  smash_csv will take two separate CSV files (each containing 
left/right PDM channel data) and smash them into a single CSV file with 4 channels.  handle_pdm
will then take that smashed CSV data, run it through a simple CIC filter, and output a 4-channel
raw PCM binary that can be imported into Audacity.

# Using

### Compiling on Windows

Use the Visual Studio project to compile.

### Compiling on Mac OSX/Linux

```bash
python build_analyzer.py
```

## Including in Saleae Logic
Set the search path for plugins to the `release` directory within your clone of
this repo.

To find the setting:

1. Open the **Options** drop down in the top right.
2. Select **Preferences**
3. Select the **Developer** tab.
4. The analyzer path is first in the pane.

Now, reload Logic and select **PDM** from the Analyzer drop down.

Please see the [Sample Analyzer](https://github.com/saleae/SampleAnalyzer/blob/master/readme.md) for detailed build instructions.
