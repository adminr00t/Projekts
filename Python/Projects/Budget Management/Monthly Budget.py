import pandas as pd

def process_transactions(input_file, output_file):
    # Load the CSV file
    df = pd.read_csv(input_file)
    
    # Convert 'Debit' and 'Credit' columns to numeric values
    df['Debit'] = df['Debit'].replace('[\$,]', '', regex=True).astype(float)
    df['Credit'] = df['Credit'].replace('[\$,]', '', regex=True).astype(float)
    
    # Fill NaN values with 0 for easier calculations
    df['Debit'].fillna(0, inplace=True)
    df['Credit'].fillna(0, inplace=True)
    
    # Extract the date (assuming format "HH:MM DD-MM-YY")
    df['Date'] = pd.to_datetime(df['Date and time'].str.extract(r'(\d{2}-\d{2}-\d{2})')[0], format="%d-%m-%y")
    
    # Remove unnecessary columns
    df.drop(columns=['Date and time', 'Receipt number', 'Transaction ID'], inplace=True, errors='ignore')
    
    # Remove internal transfers
    df = df[df['Category'] != 'Internal Transfer']
    
    # Extract month and year for grouping
    df['Month'] = df['Date'].dt.strftime('%Y-%m')
    
    # Group transactions by Month, Category, and Description (Merchant)
    grouped = df.groupby(['Month', 'Category', 'Description']).agg({'Debit': 'sum', 'Credit': 'sum'}).reset_index()
    
    # Prepare final formatted table
    final_data = []
    
    for month in grouped['Month'].unique():
        month_data = grouped[grouped['Month'] == month]
        total_expense = month_data['Debit'].sum()
        remaining = month_data['Credit'].sum() - total_expense
        
        # Append month header
        final_data.append([month, '', '', f"${total_expense:,.2f}", f"${remaining:,.2f}"])
        
        for _, row in month_data.iterrows():
            final_data.append(['', row['Category'], row['Description'], f"${row['Debit']:,.2f}", ''])
    
    # Convert to DataFrame
    formatted_df = pd.DataFrame(final_data, columns=['Month', 'Category', 'Description', 'Total Expense', 'Remaining'])
    
    # Save to Excel
    with pd.ExcelWriter(output_file) as writer:
        formatted_df.to_excel(writer, sheet_name='Monthly Budget', index=False)
    
    print(f"Monthly budget spreadsheet saved as: {output_file}")

# Example usage
if __name__ == "__main__":
    input_file = "transactions.csv"  # Update with your actual file path
    output_file = "monthly_budget.xlsx"  # Output file name
    process_transactions(input_file, output_file)
