import tabula
import re
import pandas as pd
from Components import loggingSystem
# from tabulate import tabulate

pdfPath = ""
outputPath = "./Excel Outputs"


if __name__ == '__main__':
    loggingSystem.initialize()

    pdfPath =  input("Please input path of PDF: ")
    newPath = pdfPath.replace('"',  '')
    loggingSystem.infoLog("Reading PDF...")

    pdf = tabula.read_pdf(newPath, pages='all', multiple_tables=True)[0]

    loggingSystem.infoLog("Converting to CSV...")
    tabula.convert_into(newPath, outputPath + "/ouput.csv", pages= "all")
    # pdf.to_csv(outputPath + "/output.csv")
    # pdf.to_excel(outputPath + "/output.xlsx", index=False)
